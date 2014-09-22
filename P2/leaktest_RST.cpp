#include "RST.hpp"
#include "countint.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdlib> // for rand()


using namespace std;

/**
 * A simple partial test driver for the RST class template.
 * Use with valgrind to detect basic memory leak problems.
 * P2 CSE 100
 * Author: P. Kube (c) 2010, 2013
 */
int main(int argc, char** argv) {

  int N = 1000;

  /* Create an STL vector of some random ints */
  vector<int> v;
  for(int i=0; i<N; i++) {
    v.push_back(rand());
  }

  /* Create an empty instance of RST holding int */
  BST<int>* r = new RST<int>();

  /* Insert the data items */
  cout << "Inserting " << N << " random keys in initially empty RST...";
  vector<int>::iterator vit = v.begin();
  vector<int>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    std::pair<BST<int>::iterator,bool> pr = r->insert(*vit);
  }
  
  cout << " done." << endl;
  
  cout << "deleting the RST...";
  delete r;
  cout << " done." << endl;

  cin.get();
  return 0;
}
