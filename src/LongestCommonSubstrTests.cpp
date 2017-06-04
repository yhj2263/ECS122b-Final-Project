// Copyright (c) 2017 Copyright Holder All Rights Reserved.

#include "suffixTree.h"

#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using testing::Test;

/*
 * Test class for generalized suffix tree. In this test, the input strings are
 * "aba" and "ba". The first string is ended by "$" and the second string is
 * ended by "#".
 */
class GeneralizedSuffixTree: public Test {
 public:
    suffixTree tree;
    std::string s1;
    std::string s2;
    std::string input;
    int firstLength;
    int secondLength;

    virtual void SetUp() {
        s1 = "aba";
        s2 = "ba";
        input = s1 + "$" + s2 + "#";

        firstLength = s1.length();
        secondLength = s2.length();

        tree = suffixTree(0, 0, -1);
        tree.Input = input;
        tree.inputLength = input.length() - 1;
        tree.nodeArray.resize(2*(tree.inputLength));
        tree.noOfNodes = 1;

        for (int i = 0; i <= tree.inputLength; i++) {
            tree.carryPhase(tree, i, firstLength, secondLength);
        }
    }

    virtual void TearDown() {
        tree.clearTree();
    }
};

/*
 * This test searches all possible substrings of the two input strings and
 * confirms they exist somewhere in the tree.
 */
TEST_F(GeneralizedSuffixTree, subStringSearchTest) {
    std::vector<std::string> subStrings = {"aba", "ba", "a", "ab", "b"};
    for (auto s : subStrings) {
        EXPECT_EQ(tree.search(s), true);
    }
}

TEST_F(GeneralizedSuffixTree, linkNodesTest) {
    // TODO(YHJ): Think of a way to test this.
}

/*
 * This test compare all node depth set by setDepth() fucntion to their expected
 * values, make sure the depths are correctly assigned.
 */
TEST_F(GeneralizedSuffixTree, setDepthTest) {
    ASSERT_GE(tree.nodeArray.size(), 0);
    tree.linkNodes();
    tree.setDepth(&(tree.nodeArray[0]));

    EXPECT_EQ(tree.nodeArray[0].depth, 0);
    EXPECT_EQ(tree.nodeArray[1].depth, 0);
    EXPECT_EQ(tree.nodeArray[2].depth, 0);
    EXPECT_EQ(tree.nodeArray[3].depth, 1);
    EXPECT_EQ(tree.nodeArray[4].depth, 0);
    EXPECT_EQ(tree.nodeArray[5].depth, 0);
    EXPECT_EQ(tree.nodeArray[6].depth, 2);
    EXPECT_EQ(tree.nodeArray[7].depth, 0);
    EXPECT_EQ(tree.nodeArray[8].depth, 0);
    EXPECT_EQ(tree.nodeArray[9].depth, 0);
}

/*
 * This test compares the strings labels assigned by collectLabel() funciton to their
 * expected values. Compares both C(v) values and the actual label for leaf nodes.
 */
TEST_F(GeneralizedSuffixTree, collectLabelTest) {
    ASSERT_GE(tree.nodeArray.size(), 0);
    tree.linkNodes();
    tree.collectLabel(&(tree.nodeArray[0]));

    std::vector<Node> nodeArray = tree.nodeArray;

    EXPECT_EQ(tree.nodeArray[0].getCv(), 2);
    EXPECT_EQ(tree.nodeArray[1].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[2].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[3].getCv(), 2);
    EXPECT_EQ(tree.nodeArray[4].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[5].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[6].getCv(), 2);
    EXPECT_EQ(tree.nodeArray[7].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[8].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[9].getCv(), 1);

    EXPECT_EQ(tree.nodeArray[1].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[2].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[4].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[5].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[7].stringLabels[0], 2);
    EXPECT_EQ(tree.nodeArray[8].stringLabels[0], 2);
    EXPECT_EQ(tree.nodeArray[9].stringLabels[0], 2);
}

/*
 * This test compares the strings returns by getString() function to their
 * expected values.
 */
TEST_F(GeneralizedSuffixTree, getStringTest) {
    ASSERT_GE(tree.nodeArray.size(), 0);
    tree.linkNodes();

    EXPECT_EQ(tree.getString(&tree.nodeArray[0]), "");
    EXPECT_EQ(tree.getString(&tree.nodeArray[1]), "aba$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[2]), "ba$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[3]), "a");
    EXPECT_EQ(tree.getString(&tree.nodeArray[4]), "a$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[5]), "$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[6]), "ba");
    EXPECT_EQ(tree.getString(&tree.nodeArray[7]), "ba#");
    EXPECT_EQ(tree.getString(&tree.nodeArray[8]), "a#");
    EXPECT_EQ(tree.getString(&tree.nodeArray[9]), "#");
}

/*
 * This test confirms the findLongestCommonSubstr() function returns the actual
 * longest common substring of the two input strings
 */
TEST_F(GeneralizedSuffixTree, findLongestCommonSubstrTest) {
    tree.linkNodes();
    tree.collectLabel(&(tree.nodeArray[0]));
    tree.setDepth(&(tree.nodeArray[0]));
    auto result = tree.findLongestCommonSubstr();
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "ba");
}

/*
 * This test inputs empty string and expects the returned string has size of 0
 */
TEST(LongestCommonSubstringTest, EmptyStringTest) {
    std::string s1 = "cadabd";
    std::string s2 = "";
    std::string input = "";
    std::vector<std::string> LCS;
    std::vector<std::string> result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = 0;

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();

    EXPECT_EQ(result.size(), 0);

    tree.clearTree();
}

/*
 * This test inputs two identical strings and expects the returned string to be
 * the same as input.
 */
TEST(LongestCommonSubstringTest, SameStringTest) {
    std::string s1 = "cadabd";
    std::string s2 = s1;
    std::string input = "";
    std::vector<std::string> LCS = {s1};
    std::vector<std::string> result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = s1.length();

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(LCS[0].compare(result[0]), 0);

    tree.clearTree();
}

/*
 * s1 = cadabd, s2 = adadb
 */

TEST(LongestCommonSubstringTest, TestCase1) {
    std::string s1 = "cadabd";
    std::string s2 = "adadb";
    std::string input = "";
    std::vector<std::string> LCS;
    std::vector<std::string> result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = 0;

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);

    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();
    // O(m^2n^2) naive method of finding LCS, note this method generate
    // duplicate substrings.
    for (int i = 0; i < firstLength; i++) {
        for (int j = i; j < firstLength; j++) {
            std::string substr = "";
            if (j == i) {
                substr = s1[i];
            } else {
             substr = s1.substr(i, j - i + 1);
            }
            if (s2.find(substr) != std::string::npos) {
                if (substr.length() > maxLength) {
                    maxLength = substr.length();
                    LCS.clear();
                    LCS.push_back(substr);
                } else if (substr.length() == maxLength) {
                    LCS.push_back(substr);
                } else {
                }
            }
        }
    }



    std::sort(LCS.begin(), LCS.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(result.size(), LCS.size());
    for (int i = 0; i < result.size(); i++) {
        EXPECT_EQ(LCS[i].compare(result[i]), 0);
    }

    tree.clearTree();
}

/*
 * This test inputs two string whose LCS's are not unique, using the O(m^2n^2)
 * naive method to confirm solutions.
 */
TEST(LongestCommonSubstringTest, TestCase2) {
    std::string s1 = "fdsafd";
    std::string s2 = "afsdfadsffasfr";
    std::string input = "";
    std::vector<std::string> LCS;
    std::vector<std::string> result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = 0;

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();

    // O(m^2n^2) naive method of finding LCS, note this method generate
    // duplicate substrings.
    for (int i = 0; i < firstLength; i++) {
        for (int j = i; j < firstLength; j++) {
            std::string substr = "";
            if (j == i) {
                substr = s1[i];
            } else {
             substr = s1.substr(i, j - i + 1);
            }
            if (s2.find(substr) != std::string::npos) {
                if (substr.length() > maxLength) {
                    maxLength = substr.length();
                    LCS.clear();
                    LCS.push_back(substr);
                } else if (substr.length() == maxLength) {
                    LCS.push_back(substr);
                } else {
                }
            }
        }
    }


    ASSERT_EQ(result.size(), LCS.size());
    std::sort(LCS.begin(), LCS.end());
    std::sort(result.begin(), result.end());

    for (int i = 0; i < result.size(); i++) {
        EXPECT_EQ(LCS[i].compare(result[i]), 0);
    }

    tree.clearTree();
}

/*
 * This test inputs two string whose LCS is of length 1. To make sure the
 * function works with single character.
 */
TEST(LongestCommonSubstringTest, TestCase3) {
    std::string s1 = "ba";
    std::string s2 = "aaa";
    std::string input = "";
    std::vector<std::string> LCS;
    std::vector<std::string> result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = 0;

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();
    // O(m^2n^2) naive method of finding LCS, note this method generate
    // duplicate substrings.
    for (int i = 0; i < firstLength; i++) {
        for (int j = i; j < firstLength; j++) {
            std::string substr = "";
            if (j == i) {
                substr = s1[i];
            } else {
             substr = s1.substr(i, j - i + 1);
            }
            if (s2.find(substr) != std::string::npos) {
                if (substr.length() > maxLength) {
                    maxLength = substr.length();
                    LCS.clear();
                    LCS.push_back(substr);
                } else if (substr.length() == maxLength) {
                    LCS.push_back(substr);
                } else {
                }
            }
        }
    }

    std::sort(LCS.begin(), LCS.end());
    std::sort(result.begin(), result.end());
    // Remove duplicate
    auto it = unique(LCS.begin(), LCS.end());
    LCS.resize(std::distance(LCS.begin(), it));

    ASSERT_EQ(result.size(), LCS.size());

    for (int i = 0; i < result.size(); i++) {
        EXPECT_EQ(LCS[i].compare(result[i]), 0);
    }

    tree.clearTree();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
