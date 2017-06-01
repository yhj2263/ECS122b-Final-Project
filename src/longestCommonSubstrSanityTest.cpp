#include "suffixTree.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using testing::Test;

// Buffer for input string.
string Input;
int inputLength;
// Array of nodes
std::vector<Node> nodeArray;
// The initial tree contains one node i.e. root node so count = 1;
int Node::noOfNodes = 1;
// Edges are stored in a hash table.
std::unordered_map <long, Edge> edgeHash;

#define NUM_TEST_CASES 10000
#define RANDOM_STRING_SIZE 100

TEST(GeneralizedSuffixTreeSanityTest, SimpleTest) {
    string s1 = "youodsa";
    string s2 = "dsadasf";

    Input = s1 + "$" + s2 + "#";

    int firstLength = s1.length();
    int secondLength = s2.length();
    inputLength = Input.length() - 1;

    // Creating initial suffixTree.
    suffixTree tree (0, 0, -1);
    // Allocating memory to the array of nodes.
    nodeArray.resize(2*inputLength);
    // Build the generalized suffix tree
    buildGenralizedSuffixTree(tree, firstLength, secondLength);

    //cout << "The longest common substring is " << findLongestCommonSubstr() << endl;
    EXPECT_EQ(findLongestCommonSubstr(), "dsa");
    nodeArray.clear();
    edgeHash.clear();
}

/* Sanity check for suffix tree based matching.
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
        Input = S1 + "$" + S2 + "#";
        // For aligning indices
        inputLength = Input.length() - 1;
        // Allocating memory to the array of nodes
        //nodeArray = (Node *)malloc(2*inputLength*(sizeof (Node)));
        nodeArray.resize(2*inputLength);
        //nodeArray = new Node[2*inputLength];
        suffixTree tree(0, 0, -1);

        Node::noOfNodes = 1;

        buildGenralizedSuffixTree(tree, RANDOM_STRING_SIZE, RANDOM_STRING_SIZE);

        EXPECT_EQ(search(P1), true) << "S1 " << S1 << " S2 "  << S2 << " P1 " << P1 << " P2 " << P2 << endl;
        EXPECT_EQ(search(P2), true) << "S1 " << S1 << " S2 "  << S2 << " P1 " << P1 << " P2 " << P2 << endl;

        nodeArray.clear();
        edgeHash.clear();
    }
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
