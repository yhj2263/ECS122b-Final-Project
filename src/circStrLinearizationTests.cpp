// Copyright (c) 2017 Copyright Holder All Rights Reserved.

#include "suffixTree.h"

#include <string>
#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using testing::Test;

/*
 * This test input empty string and expects the result to be an empty string
 */
TEST(circStrLinearizationTests, EmptyStringTest) {
    std::string s = "";
    std::string input;
    std::string result;
    std::vector<std::string> vec;

    // Double the string and add delimiter
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);

    tree.linkNodes();
    result = tree.linearCut(&tree.nodeArray[0]);

    EXPECT_EQ(result, "") << "Found: " << result
                          << " Expecting: " << "" << "\n";
    tree.clearTree();
}

/*
 * s = babab, expecting "ababa"
 */
TEST(circStrLinearizationTests, TestCase1) {
    std::string s = "babab";
    std::string input;
    std::string result;
    std::vector<std::string> vec;

    // Double the string and add delimiter
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);
    tree.linkNodes();
    result = tree.linearCut(&tree.nodeArray[0]);

    // Naive O(n^2) way of finding the lexically smallest linear string.
    // Iterate through all possible solution and find the smallest one.

    // Double the string
    std::string twoS = s + s;
    for (int i = 0; i < s.length(); i++) {
        std::string temp = twoS.substr(i, s.length());
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end());

    EXPECT_EQ(result.compare(vec.at(0)), 0) << "Found: " << result
            << " Expecting: " << vec.at(0) << "\n";
    tree.clearTree();
}

/*
 * s = fadsfasf, expecting adsfasf
 */
TEST(circStrLinearizationTests, TestCase2) {
    std::string s = "fadsfasf";
    std::string input;
    std::string result;
    std::vector<std::string> vec;

    // Double the string and add delimiter
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);
    tree.linkNodes();
    result = tree.linearCut(&tree.nodeArray[0]);

    // Naive O(n^2) way of finding the lexically smallest linear string.
    // Iterate through all possible solution and find the smallest one.

    // Double the string
    std::string twoS = s + s;
    for (int i = 0; i < s.length(); i++) {
        std::string temp = twoS.substr(i, s.length());
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end());

    EXPECT_EQ(result.compare(vec.at(0)), 0) << "Found: " << result
            << " Expecting: " << vec.at(0) << "\n";
    tree.clearTree();
}

/*
 * s = "zjfkaij", expecting "aijzjfk".
 */
TEST(circStrLinearizationTests, TestCase3) {
    std::string s = "zjfkaij";
    std::string input;
    std::string result;
    std::vector<std::string> vec;

    // Double the string and add delimiter
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);
    tree.linkNodes();
    result = tree.linearCut(&tree.nodeArray[0]);

    // Naive O(n^2) way of finding the lexically smallest linear string.
    // Iterate through all possible solution and find the smallest one.

    // Double the string
    std::string twoS = s + s;
    for (int i = 0; i < s.length(); i++) {
        std::string temp = twoS.substr(i, s.length());
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end());

    EXPECT_EQ(result.compare(vec.at(0)), 0) << "Found: " << result
            << " Expecting: " << vec.at(0) << "\n";
    tree.clearTree();
}

/*
 * s = aaaaa, expecting "aaaaa".
 */
TEST(circStrLinearizationTests, TestCase4) {
    std::string s = "aaaaa";
    std::string input;
    std::string result;
    std::vector<std::string> vec;

    // Double the string and add delimiter
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);
    tree.linkNodes();
    result = tree.linearCut(&tree.nodeArray[0]);

    // Naive O(n^2) way of finding the lexically smallest linear string.
    // Iterate through all possible solution and find the smallest one.

    // Double the string
    std::string twoS = s + s;
    for (int i = 0; i < s.length(); i++) {
        std::string temp = twoS.substr(i, s.length());
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end());

    EXPECT_EQ(result.compare(vec.at(0)), 0) << "Found: " << result
            << " Expecting: " << vec.at(0) << "\n";
    tree.clearTree();
}

/*
 * s = basafda, expecting "abasafd"
 */
TEST(circStrLinearizationTests, TestCase5) {
    std::string s = "basafda";
    std::string input;
    std::string result;
    std::vector<std::string> vec;

    // Double the string and add delimiter
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);
    tree.linkNodes();
    result = tree.linearCut(&tree.nodeArray[0]);

    // Naive O(n^2) way of finding the lexically smallest linear string.
    // Iterate through all possible solution and find the smallest one.

    // Double the string
    std::string twoS = s + s;
    for (int i = 0; i < s.length(); i++) {
        std::string temp = twoS.substr(i, s.length());
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end());
    ASSERT_EQ(result.length(), (vec.at(0)).length()) << result.length() << " "
        << (vec.at(0)).length() << "\n";
    EXPECT_EQ(result.compare(vec.at(0)), 0) << "Found: " << result
         << " Expecting: " << vec.at(0) << "\n";
    tree.clearTree();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
