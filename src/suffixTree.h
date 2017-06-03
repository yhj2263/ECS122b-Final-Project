#ifndef SRC_SUFFIXTREE_H_
#define SRC_SUFFIXTREE_H_

#include <unordered_map>  // Required c++11 support.
#include <iostream>
#include <vector>
#include <string>

#include "node.h"
#include "edge.h"

class suffixTree {
 public:
    int rootNode;    // Origin of the suffix tree
    int startIndex;  // Starting index of the string represented.
    int endIndex;    // End index of the string represented.
    int noOfNodes;
    std::string Input;
    int inputLength;
    std::vector<Node> nodeArray;
    std::unordered_map <int64_t, Edge> edgeHash;

    // Constructor
    suffixTree() :
        rootNode(0),
        startIndex(-1),
        endIndex(-1),
        noOfNodes(1) {}
    suffixTree(int root, int start, int end) :
        rootNode(root),
        startIndex(start),
        endIndex(end),
        noOfNodes(1) {}

    void buildTree(std::string input);
    // Real means that the suffix string ends at a node and thus the
    // remaining string on that edge would be an empty string.
    bool endReal() {return startIndex > endIndex;}
    // Img means that the suffixTree of current string ends on an imaginary
    // node, which means in between an edge.
    bool endImg() {return endIndex >= startIndex;}
    void migrateToClosestParent();

    void carryPhase(suffixTree &tree, int lastIndex);
    bool search(std::string pattern);
    void printAllEdges();


    void buildGeneralizedSuffixTree(std::string input, int firstLength,
         int secondLength);
    void carryPhase(suffixTree &tree, int lastIndex, int firstLength,
         int secondLength);
    void linkNodes();
    void collectLabel(Node* root);
    void setDepth(Node* root);
    void clearTree();
    std::string findLongestCommonSubstr();
    std::string getString(Node* node);
    std::string linearCut(Node* currNode);
    std::vector<std::string> findRepeats();

    void insert(Edge &e);
    void remove(Edge &e);
    int breakEdge(Edge &e);
    // node is the starting node and c is the ASCII input char.
    // Static because I want to call it without using an instantiated object.
    static int64_t returnHashKey(int node, int c);
    Edge findEdge(int node, int c);
};



#endif  // SRC_SUFFIXTREE_H_
