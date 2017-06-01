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

// Array of nodes.
//Node * nodeArray;
std::vector<Node> nodeArray;

// The initial tree contains one node i.e. root node so count = 1;
int Node::noOfNodes = 1;

/*
 * Edges are being stored in a hash table for better access time.
 * I was planning to use map instead of unorderedMap, but since map keeps the
 * elements in ordered fashion, it's average case time complexity is logn.
 * On the other hand, unorderedmap has a average case constant time complexity.
 * Key would be an integer which would be a function of nodeID and asciiChar
 */
unordered_map <long, Edge> edgeHash;

#define NUM_TEST_CASES 10000
#define RANDOM_STRING_SIZE 100

// Sanity check for suffix tree based matching.
// Does NUM_TEST_CASES times:
//    1) Generate random string T of size RANDOM_STRING_SIZE
//    2) Generate a random substring P of T
//    3) Builds suffix tree for T and seach for P

TEST(SuffixTreeSanityTest, SubstringMatch) {

    std::default_random_engine generator;
    std::uniform_int_distribution<int> stringDist(97, 122); // used to build random string
    std::uniform_int_distribution<int> intDist(0, RANDOM_STRING_SIZE - 1); // used to generate random substring size

    // run NUM_TEST_CASES times
    for (int k = 0; k <  NUM_TEST_CASES; k++) {

        std::string T = "";
        std::string P = "";

        char currChar;
        bool found = false;


        // randomly generate the start and end position for substring
        int begin = intDist(generator);
        int end = intDist(generator);

        if (begin < end) {
            std::swap(begin, end);
        }

        // generate a random string T of size RANDOM_STRING_SIZE
        for (int i = 0; i < RANDOM_STRING_SIZE; i++) {
            currChar = (char)stringDist(generator);
            while((currChar <= '`') && (currChar >= '[')) {
                currChar = (char)stringDist(generator);
            }
            T += currChar;
        }

        // generate a random substring
        P += T.substr(begin, end);

        // Build suffix tree for T
        Input = T;
        // For aligning indices
        inputLength = Input.length() - 1;
        // Allocating memory to the array of nodes
        //nodeArray = (Node *)malloc(2*inputLength*(sizeof (Node)));
        nodeArray.reserve(2*inputLength);
        //nodeArray = new Node[2*inputLength];
        suffixTree tree(0, 0, -1);

        Node::noOfNodes = 1;
        edgeHash.clear();
        // Carry out different phases.

        for (int i = 0; i <= inputLength; i++)
            carryPhase(tree, i);

        found = search(P);
        //delete nodeArray;
        nodeArray.clear();
        ASSERT_EQ(found, true) << T << "\n" << P << endl;
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
