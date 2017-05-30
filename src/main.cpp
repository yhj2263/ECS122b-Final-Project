#include "suffixTree.h"
#include <iostream>
#include <unordered_map> // Required c++11 support.
#include <string>
#include <cassert>
#include <ctime>
#include <chrono>
using namespace std;

// Buffer for input string.
string Input;
int inputLength;

// We need to maintain an array of nodes.
Node * nodeArray;

int main () {
  
  cout << "Enter String" << endl;
  getline(cin, Input);
  // For aligning indices
  inputLength = Input.length() - 1;

  // Allocating memory to the array of nodes.
  nodeArray = (Node *)malloc(2*inputLength*(sizeof (Node)));
//  cout << "you entered " << Input  << " length " << inputLength << endl;

  // Start timer.
  // Creating initial suffixTree.
  auto start = std::chrono::high_resolution_clock::now();
  suffixTree tree (0, 0, -1);
  // Carry out different phases.
  for (int i = 0; i <= inputLength; i++)
      carryPhase(tree, i);

  auto end = std::chrono::high_resolution_clock::now();
  printAllEdges();
  cout << "Total time taken to build suffix tree of length " << inputLength <<" : "
       << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
       << "ms"<< endl;

  cout << "Enter patterns or enter \"exit\" to exit." << endl;
  string pattern;
  getline(cin, pattern);
  while (pattern.compare("exit")) {
    search(pattern);
    cout << "----------------------------------------------------" << endl;
    cout << "Enter pattern or enter \"exit\" to exit." << endl;
    getline(cin, pattern);
  }
  cout << "Wait for some more time to see the tree." << endl;
  cout << "Seeds are being imported right now." << endl;
  cout << "Adios!" << endl;
  return 0;
}
