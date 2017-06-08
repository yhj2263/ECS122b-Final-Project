#include "suffixTree.h"

#include <cassert>

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

struct Key {
    int nodeID;
    int asciiChar;
};

void suffixTree::buildTree(std::string input) {
    Input = input;
    // The initial tree contains one node i.e. root node so count = 1;
    noOfNodes = 1;
    // For aligning indices
    inputLength = input.length() - 1;
    // Allocating memory to the array of nodes.
    nodeArray.resize(2*inputLength);
    //  cout << "you entered " << Input  << " length " << inputLength << endl;
    // Carry out different phases.
    for (int i = 0; i <= inputLength; i++)
        carryPhase(*this, i);
}

/*
 * Clear and reset all global variables to the initial state;
 */
void suffixTree::clearTree() {
    Input.clear();
    inputLength = 0;
    nodeArray.clear();
    edgeHash.clear();
    noOfNodes = 1;
}

int64_t suffixTree::returnHashKey(int nodeID, int c) {
    // long contor = (1/2)*(nodeID + c)*(nodeID + c + 1) + c;
    // return contor;
    return static_cast<int64_t>(nodeID +
                  ((static_cast<int64_t>(c)) << 57));
}

/*
 * Insert an edge into the hash table
 */
void suffixTree::insert(Edge &e) {
    int64_t key = returnHashKey(e.startNode, Input[e.startLabelIndex]);
    edgeHash[key] = e;
}

/*
 * Remove an edge from the hash table.
 */
void suffixTree::remove(Edge &e) {
    int64_t key = returnHashKey(e.startNode, Input[e.startLabelIndex]);
    edgeHash.erase(key);
}

/*
 * Find an edge in the hash table corresponding to NODE & ASCIICHAR
 */
Edge suffixTree::findEdge(int node, int asciiChar) {
    int64_t key = returnHashKey(node, asciiChar);
    auto search = edgeHash.find(key);
    if (search != edgeHash.end()) {
        return edgeHash.at(key);
    }
    // Return an invalid edge if the entry is not found.
    return Edge();
}
// rootNode should be equal to the closest node to the end of the tree so
// tht this can be used in the next iteration.
void suffixTree::migrateToClosestParent() {
    // If the current suffix tree is ending on a node, this condition is already
    // met.
    if (endReal()) {
    } else {
        Edge e = suffixTree::findEdge(rootNode, Input[startIndex]);
        // Above will always return a valid edge as we call this method after
        // adding above.
        if (e.startNode == -1) {
            cout << rootNode << " " << startIndex << " " << Input[startIndex]
                << "\n" << Input << endl;
        }
        assert(e.startNode != -1);
        int labelLength = e.endLabelIndex - e.startLabelIndex;

        // Go down
        while (labelLength <= (endIndex - startIndex)) {
            startIndex += labelLength + 1;
            rootNode = e.endNode;
            if (startIndex <= endIndex) {
                e = suffixTree::findEdge(e.endNode, Input[startIndex]);
                if (e.startNode == -1) {
                    cout << rootNode << " " << startIndex << " "
                        << Input[startIndex] << "\n" << Input<<  endl;
                }

                assert(e.startNode != -1);
                labelLength = e.endLabelIndex - e.startLabelIndex;
            }
        }
    }
}

/*
 * Break an edge so as to add new string at a specific point.
 */
int suffixTree::breakEdge(Edge &e) {
    // Remove the edge
    remove(e);

    Edge *newEdge = new Edge(rootNode, noOfNodes++, e.startLabelIndex,
                             e.startLabelIndex + endIndex - startIndex);
    insert(*newEdge);
    // Add the suffix link for the new node.
    nodeArray[newEdge -> endNode].suffixNode = rootNode;
    e.startLabelIndex += endIndex - startIndex + 1;
    e.startNode = newEdge -> endNode;
    insert(e);
    return newEdge->endNode;
}

/*
 * Main function which will carry out all the different phases of the Ukkonen's
 * algorithm. Through suffixTree we'll maintain the current position in the tree
 * and then add the prefix 0 -> lastIndex in the tree created in the previous
 * iteration.
 */
void suffixTree::carryPhase(suffixTree &tree, int lastIndex) {
    // cout << "Phase " << lastIndex << " Adding "
    //    << Input.substr(0, lastIndex + 1) << endl;
    int parentNode;
    // To keep track of the last encountered node.
    // Used for creating the suffix link.
    int previousParentNode = -1;
    while (true) {
        // First we try to match an edge for this, if there is one edge and all
        // other subsequent suffixs would already be there.
        Edge e;
        parentNode = tree.rootNode;

        // If previoustree ends in between an edge, then we need to find that
        // edge and match after that.
        if (tree.endReal()) {
            e = suffixTree::findEdge(tree.rootNode, Input[lastIndex]);
            if (e.startNode != -1)
                break;
        } else {
            e = suffixTree::findEdge(tree.rootNode, Input[tree.startIndex]);
            int diff = tree.endIndex - tree.startIndex;
            if (Input[e.startLabelIndex + diff + 1] == Input[lastIndex])
                // We have a match
                break;
            // If match was not found this way, then we need to break this edge
            // and add a node and insert the string.
            parentNode = breakEdge(e);
        }

        // We have not matchng edge at this point, so we need to create a new
        // one, add it to the tree at parentNode position and then insert it
        // into the hash table.
        //
        // We are creating a new node here, which means we also need to update
        // the suffix link here. Suffix link from the last visited node to the
        // newly created node.
        Edge *newEdge = new Edge(parentNode, noOfNodes++, lastIndex,
             inputLength);

        insert(*newEdge);
        if (previousParentNode > 0) {
            nodeArray[previousParentNode].suffixNode = parentNode;
        }
        previousParentNode = parentNode;

        // Move to next suffix, i.e. next extension.
        if (tree.rootNode == 0) {
            tree.startIndex++;
        } else {
            tree.rootNode = nodeArray[tree.rootNode].suffixNode;
        }
        tree.migrateToClosestParent();
    }

    if (previousParentNode > 0) {
        nodeArray[previousParentNode].suffixNode = parentNode;
    }
    tree.endIndex++;
    tree.migrateToClosestParent();
}

/*
 * This function takes argument "pattern", searches for pattern in the tree and
 * return true if "pattern" is found.
 */
bool suffixTree::search(std::string pattern) {
    if ("" == pattern) {
        return true;
    }
    int len = pattern.length();
    // Starting from 0 we start searching the pattern.
    Edge e = findEdge(0, pattern[0]);
    // index until where we have matched on edge.
    int iter = 0;
    int i = -1;
    if (e.startNode != -1) {
        while (i < len) {
            iter = 0;
            // cout << "Search:\tEdge: " << e.startNode << " " << e.endNode
            //    << " : " << Input[e.startLabelIndex]  << " "
            //    << Input[e.endLabelIndex] << " I: " << i << endl;
            // Match this edge as much as possible.
            while (e.endLabelIndex >= e.startLabelIndex + iter) {
            //    cout << "Search:\tmatching " << Input[e.startLabelIndex + iter]
            //        << " "  << pattern[i + iter + 1]
            //        << " at index: " << e.startLabelIndex + iter << endl;
                // If character matches we increase the iterator
                // otherwise we are done. No match.
                if (Input[e.startLabelIndex + iter] == pattern[i + iter + 1]) {
                    iter++;
                    // If we have a match in the middle then we are done.
                    if (i + iter  + 1 >= len) {
                    //        cout << "Search:\tWe have a match ending at "
                    //             << e.startLabelIndex + iter  - 1 << endl;
                        return true;
                    }
                } else {
                //    cout << "Search:\tMatch not found, matched only upto index:"
                //        << i+iter << endl;
                    return false;
                }
            }
            // We have done all possible matches on this edge. We can proceed
            // only if the entire label matches.
            assert(iter = (e.endLabelIndex - e.startLabelIndex + 1));

            // Now we need to find another edge to match.
            e = suffixTree::findEdge(e.endNode, pattern[i + iter + 1]);
            if (e.startNode == -1) {
                return false;
            }
            i+=(iter);
        }
    }
    return true;
}

/*
 * This function prints all the edges in the suffix tree.
 */
void suffixTree::printAllEdges() {
    int count = 0;
    cout << "StartNode\tEndNode\tSuffixLink\tFirstIndex\tlastIndex\tString"
        << endl;
    // For auto : C++11 FTW :)
    for (auto it = edgeHash.begin(); it != edgeHash.end(); it++) {
        cout << it -> second.startNode << "\t\t" << it -> second.endNode
             //<< "\t\t" << nodeArray[it -> second.endNode].suffixNode
             << "\t\t" << nodeArray[it -> second.endNode].suffixNode
             << "\t\t" << it -> second.startLabelIndex
             << "\t\t" << it -> second.endLabelIndex
             << "\t\t";
        count++;
        int head;
        if (inputLength > it -> second.endLabelIndex)
            head = it -> second.endLabelIndex;
        else
            head = inputLength;
        for (int i = it -> second.startLabelIndex; i < head + 1; i++)
            cout << Input[i];
        cout << endl;
    }
    cout << "Total edges: " << count << endl;
}

// ****************************************************************** //
// ********** Added functions for generalized suffix tree *********** //
// ****************************************************************** //

/*
 * This function basiclly do the same job as the original carryPhase function.
 * With added arguments @firstLength and @secondLength, it's able to handle two
 * input strings and construct a generalized suffix tree.
 */
void suffixTree::carryPhase(suffixTree &tree, int lastIndex, int firstLength,
     int secondLength) {
    // cout << "Phase " << lastIndex << " Adding "
    //    << Input.substr(0, lastIndex + 1) << endl;
    int parentNode;
    // To keep track of the last encountered node.
    // Used for creating the suffix link.
    int previousParentNode = -1;
    while (true) {
        // First we try to match an edge for this, if there is one edge and all
        // other subsequent suffixs would already be there.
        Edge e;
        parentNode = tree.rootNode;

        // If previoustree ends in between an edge, then we need to find that
        // edge and match after that.
        if (tree.endReal()) {
            e = suffixTree::findEdge(tree.rootNode, Input[lastIndex]);
            if (e.startNode != -1) {
                break;
            }
        } else {
            e = suffixTree::findEdge(tree.rootNode, Input[tree.startIndex]);
            int diff = tree.endIndex - tree.startIndex;
            if (Input[e.startLabelIndex + diff + 1] == Input[lastIndex]) {
                // We have a match
                break;
            }
            // If match was not found this way, then we need to break this edge
            // and add a node and insert the string.
            parentNode = breakEdge(e);
        }
        // We have not matchng edge at this point, so we need to create a new
        // one, add it to the tree at parentNode position and then insert it
        // into the hash table.
        //
        // We are creating a new node here, which means we also need to update
        // the suffix link here. Suffix link from the last visited node to the
        // newly created node.
        Edge *newEdge;
        if (lastIndex <= firstLength) {
            newEdge = new Edge(parentNode, noOfNodes++, lastIndex, firstLength);
        } else {
            newEdge = new Edge(parentNode, noOfNodes++, lastIndex, inputLength);
        }
        insert(*newEdge);
        if (previousParentNode > 0)
            nodeArray[previousParentNode].suffixNode = parentNode;
        previousParentNode = parentNode;
        // Move to next suffix, i.e. next extension.
        if (tree.rootNode == 0) {
            tree.startIndex++;
        } else {
            tree.rootNode = nodeArray[tree.rootNode].suffixNode;
        }
        tree.migrateToClosestParent();
    }
    if (previousParentNode > 0) {
        nodeArray[previousParentNode].suffixNode = parentNode;
    }
    tree.endIndex++;
    tree.migrateToClosestParent();
}

/*
 * The original implementation represents the suffix tree by its edges, all
 * edges are stored in a hashtable. In order to search for the longest common
 * substring, we need to construct the actual tree structure where we can
 * traverse the tree from rootNode.
 */
void suffixTree::linkNodes() {
    if (nodeArray.size() <= 1) return;
    // Assign ID for each node
    for (int i = 0; i < nodeArray.size(); i++) {
        nodeArray[i].nodeID = i;
    }
    // Traverse all edges and construct the tree, assign string labels to leaf.
    for (auto it = edgeHash.begin(); it != edgeHash.end(); it++) {
        // Link the endNode to startNode
        (nodeArray[it->second.startNode].childNodes).push_back(
            &nodeArray[it->second.endNode]);
        // Record the edge length
        (nodeArray[it->second.endNode].edgeLength) =
        it->second.endLabelIndex - it->second.startLabelIndex + 1;
        // Record the incoming edge
        (nodeArray[it->second.endNode].incomeEdge) = &it->second;
        // Assign string labels. "$" is assigned "1" and "#" is assigned "2".
        if ('$' == Input[it->second.endLabelIndex]) {
            nodeArray[it->second.endNode].stringLabels.push_back(1);
        } else if ('#' == Input[it->second.endLabelIndex]) {
            nodeArray[it->second.endNode].stringLabels.push_back(2);
        }
    }
}

/*
 * DFS traversal to assign depth to all nodes
 */
void suffixTree::setDepth(Node* root) {
    for (auto childNode : root->childNodes) {
        if (!childNode->isLeaf()) {
            childNode->depth = root->depth + childNode->edgeLength;
            setDepth(childNode);
        }
    }
}

/*
 * DFS traversal to collect string labels for internal nodes
 */
void suffixTree::collectLabel(Node* root) {
    if (root->isLeaf()) return;
    for (auto childNode : root->childNodes) {
        // If the child is a leaf, add its label to current node
        if (childNode->isLeaf()) {
            auto label = childNode->stringLabels[0];
            auto begin = (root->stringLabels).begin();
            auto end = (root->stringLabels).end();
            auto found = std::find(begin, end, label);
            // Do nothing if the label already exists , else add the label
            if (found != end) {
            } else {
                root->stringLabels.push_back(label);
            }
        } else {
            // Not a leaf, DFS then add its label to current node
            collectLabel(childNode);
            for (auto label : childNode->stringLabels) {
                auto begin = (root->stringLabels).begin();
                auto end = (root->stringLabels).end();
                auto found = std::find(begin, end, label);
                // Do nothing if the label already exists , else add the label
                if (found != end) {
                } else {
                    root->stringLabels.push_back(label);
                }
            }
        }
    }
}
/*
 * This function take a node as its argument and return the string label from
 * root to this node. Labels are collected by looking at the incoming edge to
 * that node and traveling along edges all the way to the root node.
 */
std::string suffixTree::getString(Node* node) {
    std::string ret;
    if (nullptr == node) {
        return ret;
    }
    // If the node is root, return the empty string.
    if (node->isRoot()) {
        return ret;
    }
    // Read the incoming edge and make sure such edge exists.
    auto edge = node->incomeEdge;
    if (nullptr == edge) {
        return ret;
    }

    // Read the parent node from the edge.
    auto parentNode = nodeArray[edge->startNode];
    // Collect the string represented by current edge.
    int head;
    if (inputLength > edge->endLabelIndex)
        head = edge->endLabelIndex;
    else
        head = inputLength;
    for (int i = edge->startLabelIndex; i < head + 1; i++) {
        ret += Input[i];
    }
    // Recursively collect string labels
    ret = getString(&parentNode) + ret;
    return ret;
}

/*
 * This funciton looks at all nodes with both string delimiters and finds the node
 * with largest depth. The string label from the root to that node is the
 * longest common substring of the two input strings. If there exists multiple
 * such string, they will be all returned in a vector.
 */
std::vector<std::string> suffixTree::findLongestCommonSubstr() {
    std::vector<std::string> currLongest;
    int maxLength = 0;
    for (int i = 0; i < nodeArray.size(); i++) {
        Node* node = &nodeArray[i];
        // The path label to current node is a common substring iff both two
        // string delimiters are in its subtree.
        if (2 == node->getCv()) {
            // If the node depth is greater than current max, set its depth as
            // new max, clear the return list and save it.
            // Else if the node depth is the same as current max, save it to the
            // return list.
            if (node->depth > maxLength) {
                maxLength = node->depth;
                currLongest.clear();
                currLongest.push_back(getString(node));
            } else if ((node->depth == maxLength) && (maxLength != 0)) {
                currLongest.push_back(getString(node));
            }
        }
    }
    return currLongest;
}

/*
 * This function carrys all the phases, calls linkNodes(), collectLabels() and
 * setDepth() to build the actual tree.
 */
void suffixTree::buildGeneralizedSuffixTree(std::string input, int firstLength,
     int secondLength) {
    Input = input;
    // The initial tree contains one node i.e. root node so count = 1;
    noOfNodes = 1;
    // For aligning indices
    inputLength = input.length() - 1;
    // Allocating memory to the array of nodes.
    nodeArray.resize(2*inputLength);
    // Carry each phase
    for (int i = 0; i <= inputLength; i++) {
        carryPhase(*this, i, firstLength, secondLength);
    }
    // Link all nodes based on the hash tabel and construct the tree
    linkNodes();
    // collect string labels for internal nodes.
    collectLabel(&nodeArray[0]);
    // Set depth for internal nodes.
    setDepth(&nodeArray[0]);
}
// ****************************************************************** //
// ********** Added functions for finding maximal repeats *********** //
// ****************************************************************** //
/*
 * This function finds all repeated pattern based on a constructed suffix tree.
 * Basiclly, every internal node represents a repeated substring.
 */
// TODO(YHJ): Add ability to find maximal repeats.
std::vector<std::string> suffixTree::findRepeats() {
    std::vector<std::string> repeats;
    for (auto node : nodeArray) {
        if (!(node.isRoot()) && !(node.isLeaf())) {
            auto s = getString(&node);
            repeats.push_back(s);
        }
    }
    return repeats;
}
// ****************************************************************** //
// ******* Added functions for circular string linearization ******** //
// ****************************************************************** //

/*
 * This function returns the lexically smallest lienar string based on a built
 * suffix tree. It traverses the tree starting from the root. At each internal
 * node, it looks through the childNodes vector and locates the edge starting
 * with the lexically smallest character and continues.
 */
std::string suffixTree::linearCut(Node* currNode) {
    std::string ret;
    char minChar = '{';  // ASCII 123, right after "z".
    Node* minNode = nullptr;
    Edge* minEdge = nullptr;

    // Return if the node is a leaf.
    if ((nullptr == currNode) || (currNode->isLeaf())) {
        return ret;
    }
    // Go through all childNodes and find the smallest edge
    for (auto node : currNode->childNodes) {
        Edge* edge = node->incomeEdge;
        if (nullptr == edge) {
            std::cerr << "Edge missing between " << currNode->nodeID << " and "
                      << node->nodeID << "\n";
            break;
        }
        // Find a smaller edge, record it.
        if (Input[edge->startLabelIndex] < minChar) {
            minChar = Input[edge->startLabelIndex];
            minNode = node;
            minEdge = edge;
        }
    }
    if (nullptr == minNode) {
        std::cerr << "minNode missing for node " << currNode->nodeID << "\n";
        return ret;
    }
    // Read the label on that edge
    // TODO(YHJ): Maybe consider refactoring this into a single function
    int head;
    if (inputLength > minEdge->endLabelIndex)
        head = minEdge->endLabelIndex;
    else
        head = inputLength;
    for (int i = minEdge->startLabelIndex; i < head + 1; i++) {
        ret += Input[i];
    }
    // Recursively collect the label
    ret = ret + linearCut(minNode);
    // Calling this function with root returns the lexically smallest linear cut
    if (currNode->isRoot()) {
        if (ret.length() < (Input.length()-1)/2) {
            std::cerr << "Linearization does not generate correct length\n";
            return ret;
        }
        return ret.substr(0, (Input.length()-1)/2);
    }

    return ret;
}
