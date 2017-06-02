#include "suffixTree.h"
#include <iostream>
#include <unordered_map> // Required c++11 support.
#include <string>
// Buffer for input string.
std::string Input;
int inputLength;

// We need to maintain an array of nodes.
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
std::unordered_map <long, Edge> edgeHash;

int main() {

    std::string s;
    cout << "Enter String" << endl;
    getline(cin, s);
    // Add delimiters to both end
    Input = s + s + "{";
    // For aligning indices
    inputLength = Input.length() - 1;

    // Allocating memory to the array of nodes.
    nodeArray.resize(2*inputLength);
    //  cout << "you entered " << Input  << " length " << inputLength << endl;

    // Creating initial suffixTree.
    suffixTree tree (0, 0, -1);
    // Carry out different phases.
    for (int i = 0; i <= inputLength; i++)
        carryPhase(tree, i);

    linkNodes();

    printAllEdges();

    cout << "linearization result: " << linearCut(&nodeArray[0]) << "\n";
    return 0;
}
