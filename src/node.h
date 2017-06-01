#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

class Edge;

class Node {
public:
    static int noOfNodes;
    int suffixNode;
    // each node has a unique ID, rootNode has ID 0.
    int nodeID;
    // the depth used to find longest common substring.
    int depth;
    // record the length of the incoming edge
    int edgeLength;
    // TODO find a better way to store labels.
    Edge* incomeEdge;
    std::vector<int> stringLabels;
    // save all childNodes in a vector, a leaf node does not have any child.
    std::vector<Node*> childNodes;

    Node () :
        suffixNode(-1), nodeID(-1), depth(0), edgeLength(0), incomeEdge(nullptr) {};
    ~Node() {
       //  cout << "destroying node " << id << endl;
    }

    // return true if this node a leaf, false otherwise.
    bool isLeaf(){
        return childNodes.empty();
    }
    // return the string label
    std::vector<int> getStrLabel(){
        return stringLabels;
    }
    //return the C(v) value
    int getCv(){
        return stringLabels.size();
    }
    bool isRoot(){
        return (0 == nodeID);
    }
};
#endif
