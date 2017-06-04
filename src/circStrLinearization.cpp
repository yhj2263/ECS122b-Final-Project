// Copyright (c) 2017 Copyright Holder All Rights Reserved.

#include "suffixTree.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

/*
 *
 */
int main() {
    std::string s;
    std::string input;
    std::string result;
    // Prompt the input string from user
    cout << "Enter String" << endl;
    getline(std::cin, s);
    // Double the string and add delimiter, '{' is lexically larger than 'z'.
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);
    tree.linkNodes();
    tree.printAllEdges();

    result = tree.linearCut(&tree.nodeArray[0]);
    cout << "Linearization result: " << result << "\n";

    // Double the string
    std::string twoS = s + s;
    std::vector<std::string> vec;
    for (int i = 0; i < s.length(); i++) {
        std::string temp = twoS.substr(i, s.length());
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end());
    cout << "By naive method, the lexically samllest string is: " << vec.at(0)
            << "\n";

    if (result.compare(vec.at(0)) == 0) {
        cout << "The two results are the same\n";
    }
    return 0;
}
