#include "suffixTree.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using testing::Test;

#define NUM_TEST_CASES 10000
#define RANDOM_STRING_SIZE 100

/* Sanity check for genralized suffix tree based matching.
 * Does NUM_TEST_CASES times:
 * 1) Generate random strings S of size RANDOM_STRING_SIZE.
 * 2) Builds suffix tree for S.
 * 3) Find the lexically smallest cut by both suffix tree and naive method.
 * 4) Search the result returned by both method.
 */
TEST(circStrLinearizationSanityTests, RandomStringTest) {
    std::default_random_engine generator;
    // used to build random string
    std::uniform_int_distribution<int> stringDist(97, 122);
    // used to generate random substring size
    std::uniform_int_distribution<int> intDist(0, RANDOM_STRING_SIZE - 1);


    char currChar;

    for (int k = 0; k <  NUM_TEST_CASES; k++) {
        std::string S;
        std::string input;
        std::string result;
        std::vector<std::string> vec;

        if ((0 == k % 2000) && (k != 0)) {
            cout << "**** " << k << " test cases passed ****" << endl;
        }

        // generate a random string S of size RANDOM_STRING_SIZE
        for (int i = 0; i < RANDOM_STRING_SIZE; i++) {
            currChar = (char)stringDist(generator);
            while((currChar <= '`') && (currChar >= '[')) {
                currChar = (char)stringDist(generator);
            }
            S += currChar;
        }

        input = S + S + "}";
        suffixTree tree (0, 0, -1);
        tree.buildTree(input);
        tree.linkNodes();
        result = tree.linearCut(&tree.nodeArray[0]);

        std::string twoS = S + S;
        // At least n possible cuts
        vec.reserve(S.length());
        for (int i = 0; i < S.length(); i++) {
            std::string temp = twoS.substr(i, S.length());
            vec.push_back(temp);
        }
        std::sort(vec.begin(), vec.end());

        ASSERT_NE(vec.size(), 0);
        EXPECT_EQ(result.compare(vec.at(0)), 0) << "Found: " << result
            << " Expecting: " << vec.at(0) << "\n";
        tree.clearTree();
    }
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
