#include "suffixTree.h"
#include <iostream>
#include <string>
#include <cassert>
#include <ctime>
#include <chrono>
using namespace std;

int main () {
  std::string input;
  cout << "Enter String" << endl;
  getline(cin, input);

  // Start timer.
  auto start = std::chrono::high_resolution_clock::now();
  // Creating initial suffixTree.
  suffixTree tree (0, 0, -1);


  auto end = std::chrono::high_resolution_clock::now();
  tree.buildTree(input);
  tree.printAllEdges();
  cout << "Total time taken to build suffix tree of length " << input.length()-1 <<" : "
       << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
       << "ms"<< endl;

  cout << "Enter patterns or enter \"exit\" to exit." << endl;
  std::string pattern;
  getline(cin, pattern);
  while (pattern.compare("exit")) {
    tree.search(pattern);
    cout << "----------------------------------------------------" << endl;
    cout << "Enter pattern or enter \"exit\" to exit." << endl;
    getline(cin, pattern);
  }
  cout << "Wait for some more time to see the tree." << endl;
  cout << "Seeds are being imported right now." << endl;
  cout << "Adios!" << endl;
  return 0;
}
