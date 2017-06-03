#include "suffixTree.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using testing::Test;

#define NUM_TEST_CASES 10000
#define RANDOM_STRING_SIZE 100

TEST(GeneralizedSuffixTreeSanityTest, SimpleTest) {
    string s1 = "youodsa";
    string s2 = "dsadasf";

    std::string input = s1 + "$" + s2 + "#";

    int firstLength = s1.length();
    int secondLength = s2.length();

    // Creating initial suffixTree.
    suffixTree tree (0, 0, -1);
    // Build the generalized suffix tree
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    //cout << "The longest common substring is " << findLongestCommonSubstr() << endl;
    EXPECT_EQ(tree.findLongestCommonSubstr(), "dsa");
    tree.clearTree();
}

/* Sanity check for genralized suffix tree based matching.
 * Does NUM_TEST_CASES times:
 * 1) Generate random strings S1 and S2 of size RANDOM_STRING_SIZE
 * 2) Builds generalized suffix tree for S1 and S2
 * 3) Genrate random substring of S1 and S2
 * 4) Search for P1 and P2
 */
TEST(GeneralizedSuffixTreeSanityTest, SubStringMatching) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> stringDist(97, 122); // used to build random string
    std::uniform_int_distribution<int> intDist(0, RANDOM_STRING_SIZE - 1); // used to generate random substring size

    // run NUM_TEST_CASES times
    for (int k = 0; k <  NUM_TEST_CASES; k++) {
        if ((0 == k % 2000) && (k != 0)) {
            cout << "**** " << k << " test cases passed ****" << endl;
        }
        std::string S1 = "";
        std::string S2 = "";
        std::string P1 = "";
        std::string P2 = "";
        std::string input = "";

        char currChar;
        bool found = false;


        // randomly generate the start and end position for substring
        int begin;
        int end;

        // generate a random string T of size RANDOM_STRING_SIZE
        for (int i = 0; i < RANDOM_STRING_SIZE; i++) {
            currChar = (char)stringDist(generator);
            while((currChar <= '`') && (currChar >= '[')) {
                currChar = (char)stringDist(generator);
            }
            S1 += currChar;

            currChar = (char)stringDist(generator);
            while((currChar <= '`') && (currChar >= '[')) {
                currChar = (char)stringDist(generator);
            }
            S2 += currChar;
        }

        // generate a random substring for S1
        begin = intDist(generator);
        end = intDist(generator);

        if (begin < end) {
            std::swap(begin, end);
        }
        P1 += S1.substr(begin, end);

        begin = intDist(generator);
        end = intDist(generator);

        if (begin < end) {
            std::swap(begin, end);
        }
        P2 += S2.substr(begin, end);

        //cout << "S1 " << S1 << " S2 "  << S2 << " P1 " << P1 << " P2 " << P2 << endl;
        // Build suffix tree for T
        input = S1 + "$" + S2 + "#";

        suffixTree tree(0, 0, -1);

        tree.buildGeneralizedSuffixTree(input, RANDOM_STRING_SIZE, RANDOM_STRING_SIZE);

        EXPECT_EQ(tree.search(P1), true) << "S1 " << S1 << " S2 "  << S2 << " P1 " << P1 << " P2 " << P2 << endl;
        EXPECT_EQ(tree.search(P2), true) << "S1 " << S1 << " S2 "  << S2 << " P1 " << P1 << " P2 " << P2 << endl;

        tree.clearTree();
    }
}

/* Sanity check for the length of returned longest common substring.
 * Does NUM_TEST_CASES times:
 * 1) Generate random string S with a random size less than RANDOM_STRING_SIZE
 * 2) Generate random string S1 and S2 by extending S
 * 3) Builds generalized suffix tree for S1 and S2
 * 4) Find the longest common substring of S1 and S2
 *
 * Since S1 and S2 are generated by extending S, they should have a common
 * substring of at least length |S|. This test check for the length of the
 * returned longest common substring by comparing with the length of S.
 */
TEST(LongestCommonSubstrSanityTest, ExtendSameStringTest) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> stringDist(97, 122); // used to build random string
    std::uniform_int_distribution<int> intDist(0, RANDOM_STRING_SIZE - 1); // used to generate random substring size

    // Run NUM_TEST_CASES times
    for (int k = 0; k <  NUM_TEST_CASES; k++) {
        if ((0 == k % 2000) && (k != 0)) {
            cout << "**** " << k << " test cases passed ****" << endl;
        }
        std::string S = "";
        std::string S1 = "";
        std::string S2 = "";
        std::string input = "";

        char currChar;

        // Randomly generate the start and end position for substring
        int randLength = intDist(generator);
        std::uniform_int_distribution<int> posDist(0, RANDOM_STRING_SIZE - randLength - 1);

        // Generate a random string S of random size
        for (int i = 0; i < randLength; i++) {
            currChar = (char)stringDist(generator);
            S += currChar;
        }

        // Generate a random string S1 by extending S
        // Generate a random position for S in S1
        int randPos = posDist(generator);
        for (int i = 0; i < randPos; i++) {
            currChar = (char)stringDist(generator);
            S1 += currChar;
        }
        S1 += S;
        for (int i = 0; i < (RANDOM_STRING_SIZE - randLength - randPos); i++) {
            currChar = (char)stringDist(generator);
            S1 += currChar;
        }

        randPos = posDist(generator);
        for (int i = 0; i < randPos; i++) {
            currChar = (char)stringDist(generator);
            S2 += currChar;
        }
        S2 += S;
        for (int i = 0; i < (RANDOM_STRING_SIZE - randLength - randPos); i++) {
            currChar = (char)stringDist(generator);
            S2 += currChar;
        }

        ASSERT_NE(S1.find(S), std::string::npos);
        ASSERT_NE(S2.find(S), std::string::npos);

        // Build suffix tree for T

        input = S1 + "$" + S2 + "#";

        suffixTree tree(0, 0, -1);

        tree.buildGeneralizedSuffixTree(input, RANDOM_STRING_SIZE, RANDOM_STRING_SIZE);

        auto found = tree.findLongestCommonSubstr();

        EXPECT_GE(found.length(), randLength) << "found " << found.length() << " expecting " << randLength << endl;

        tree.clearTree();
    }
}

TEST(LongestCommonSubstrSanityTest, RandomStringTest) {
    // TODO Add this test
}



int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
