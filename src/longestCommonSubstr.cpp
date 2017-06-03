#include "suffixTree.h"
#include <iostream>
#include <unordered_map> // Required c++11 support.
#include <string>
using namespace std;

int main () {
    std::string s1;
    std::string s2;
    std::string input;
    std::cout << "Enter the first string" << std::endl;
    getline(cin, s1);
    std::cout << "Enter the second string" << std::endl;
    getline(cin, s2);
    // For aligning indices
    input = s1 + "$" + s2 + "#";

    int firstLength = s1.length();
    int secondLength = s2.length();

    suffixTree tree (0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);
    tree.printAllEdges();
    cout << "The longest common substring is " << tree.findLongestCommonSubstr() << endl;
}
