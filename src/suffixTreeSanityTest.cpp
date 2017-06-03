// Copyright (c) 2017 Copyright Holder All Rights Reserved.
#include "suffixTree.h"

#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <utility>

#include "gtest/gtest.h"

using testing::Test;

#define NUM_TEST_CASES 10000
#define RANDOM_STRING_SIZE 100

// Sanity check for suffix tree based matching.
// Does NUM_TEST_CASES times:
//    1) Generate random string T of size RANDOM_STRING_SIZE
//    2) Generate a random substring P of T
//    3) Builds suffix tree for T and seach for P

TEST(SuffixTreeSanityTest, SubstringMatch) {
    std::default_random_engine generator;
    // used to build random string.
    std::uniform_int_distribution<int> stringDist(97, 122);
    // used to generate random substring size.
    std::uniform_int_distribution<int> intDist(0, RANDOM_STRING_SIZE - 1);

    // Run NUM_TEST_CASES times.
    for (int k = 0; k <  NUM_TEST_CASES; k++) {
        if ((0 == k % 2000) && (k != 0)) {
            cout << "**** " << k << " test cases passed ****" << endl;
        }

        std::string T = "";
        std::string P = "";

        char currChar;
        bool found = false;


        // Randomly generate the start and end position for substring.
        int begin = intDist(generator);
        int end = intDist(generator);

        if (begin < end) {
            std::swap(begin, end);
        }

        // Generate a random string T of size RANDOM_STRING_SIZE
        for (int i = 0; i < RANDOM_STRING_SIZE; i++) {
            currChar = static_cast<char>(stringDist(generator));
            while ((currChar <= '`') && (currChar >= '[')) {
                currChar = static_cast<char>(stringDist(generator));
            }
            T += currChar;
        }

        // Generate a random substring.
        P += T.substr(begin, end);
        suffixTree tree(0, 0, -1);
        tree.buildTree(T);
        found = tree.search(P);
        tree.clearTree();
        ASSERT_EQ(found, true) << T << "\n" << P << endl;
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
