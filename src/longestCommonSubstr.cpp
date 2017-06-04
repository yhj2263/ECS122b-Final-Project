// Copyright (c) 2017 Copyright Holder All Rights Reserved.

#include "suffixTree.h"
#include <iostream>
#include <unordered_map>  // Required c++11 support.
#include <string>

using std::cout;

int main() {
    std::string s1;
    std::string s2;
    std::string input;
    std::cout << "Enter the first string" << std::endl;
    getline(std::cin, s1);
    std::cout << "Enter the second string" << std::endl;
    getline(std::cin, s2);

    s1 = "pjkjjnxqmheyjrctfsvtdarfrrfrixnsmsmsdmtdvyooxerplkevagygfeiazghdkfxxmadpwioxtowsvshgqbgcydvzdfhhqnbx";
    s2 = "ynzgjpiowxnfnwjqeyeqooymbxsonwtumvbimfqfcwopeebcincbwqloyvotehdvrxkbxqajxyxvjebpnboncdofnbxjqbhuduve";

    if (s2.find("nbx") != std::string::npos) { cout << "nbx exists" << "\n";}

    // For aligning indices
    input = s1 + "$" + s2 + "#";

    int firstLength = s1.length();
    int secondLength = s2.length();

    cout << "s1: " <<  firstLength << " s2: " << secondLength << "\n";

    suffixTree tree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);
    //tree.printAllEdges();
    auto result = tree.findLongestCommonSubstr();
    std::sort(result.begin(), result.end());
    if (0 == result.size()) {
        cout << "These two string has no common substring\n";
    } else if (1 == result.size()) {
        cout << "The longest common substring is " << result[0] << "\n";
    } else {
        cout << "There are " << result.size() << " strings of size "
            << result[0].length() << " : \n";
        for (auto s : result) {
            cout << s << "\n";
        }
    }

    std::vector<std::string> LCS;
    int maxLength = 0;
    // O(m^2n^2) naive method of finding LCS
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
    // Remove duplicate strings
    auto it = std::unique(LCS.begin(), LCS.end());
    LCS.resize(std::distance(LCS.begin(), it));
    cout << "By naive method, there are " << LCS.size() << " strings of size "
        << LCS[0].length() << " : \n";

    for (auto s : LCS) {
        cout << s << "\n";
    }
    return 0;
}
