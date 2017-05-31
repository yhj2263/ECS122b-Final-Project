#include "suffixTree.h"
#include <iostream>
#include <unordered_map> // Required c++11 support.
#include <string>
using namespace std;

// Buffer for input string.
string Input;
int inputLength;

// We need to maintain an array of nodes.
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

int main () {
    string s1;
    string s2;
    std::cout << "Enter the first string" << std::endl;
    getline(cin, s1);
    std::cout << "Enter the second string" << std::endl;
    getline(cin, s2);
    // For aligning indices
    Input = s1 + "$" + s2 + "#";

    int firstLength = s1.length();
    int secondLength = s2.length();
    inputLength = Input.length() - 1;


    //nodeArray = (Node *)malloc(2*inputLength*(sizeof (Node)));
    //nodeArray.reserve(2*inputLength);
    //  cout << "you entered " << Input  << " length " << inputLength << endl;

    // Creating initial suffixTree.
    suffixTree tree (0, 0, -1);
    // Allocating memory to the array of nodes.
    nodeArray.resize(2*inputLength);
    // Carry out different phases.
    for (int i = 0; i <= inputLength; i++){
        carryPhase(tree, i, firstLength, secondLength);
        printAllEdges();
    }

    // Link all nodes based on the hash tabel and construct the tree/
    linkNodes();
    

    return 0;
}
