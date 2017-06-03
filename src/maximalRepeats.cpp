#include "suffixTree.h"

#include <iostream>
#include <string>
#include <vector>

/*
 *
 */
int main() {
    std::string s;
    std::string input;

    cout << "Enter String" << endl;
    getline(std::cin, s);
    // Add delimiters to both end
    input = "$" + s + "#";

    suffixTree tree(0, 0, -1);
    tree.buildTree(input);

    tree.linkNodes();

    tree.printAllEdges();

    std::vector<std::string> repeats = tree.findRepeats();

    for (auto s : repeats) {
        std::cout << s << " ";
    }
    std::cout << "\n";

    return 0;
}
