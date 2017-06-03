// Copyright (c) 2017 Copyright Holder All Rights Reserved.

#include "suffixTree.h"

#include <iostream>
#include <string>

/*
 *
 */
int main() {
    std::string s;
    std::string input;
    cout << "Enter String" << endl;
    getline(std::cin, s);
    // Double the string and add delimiter
    input = s + s + "{";
    // Build the initial tree
    suffixTree tree(0, 0, -1);
    tree.buildTree(input);

    tree.printAllEdges();

    cout << "linearization result: " << tree.linearCut(&tree.nodeArray[0])
        << "\n";
    return 0;
}
