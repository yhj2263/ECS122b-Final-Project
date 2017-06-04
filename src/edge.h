
#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <iostream>
#include "node.h"
using std::cout;
using std::endl;

class Edge {
 public:
    // Edges are hash-searched on the basis of startNode.
    // startNode = -1 means that this edge is not valid yet.
    int startNode;
    int endNode;
    int startLabelIndex;
    int endLabelIndex;

    // Constructors.
    Edge() : startNode(-1) {}
    // everytime a new edge is created, a new node is also created and thus the
    // endNode is declared as below.
    Edge(int start, int end, int first, int last) :
        startNode(start),
        endNode(end),
        startLabelIndex(first),
        endLabelIndex(last) {}
    // Destructor
    ~Edge() {}
};

#endif  // SRC_EDGE_H_
