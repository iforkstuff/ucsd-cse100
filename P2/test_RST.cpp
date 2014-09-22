#include "RST.hpp"
#include "countint.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

/**
 * A simple partial test driver for the RST class template.
 * P2 CSE 100
 * Author: P. Kube (c) 2010, 2013
 */
int main(int argc, char** argv) {

	srand(time(0));

  int N = 1000;
  if(argc > 1) N = atoi(argv[1]);
  // a good RST implementation should need no more than this number
  // of key comparisons when inserting N keys
  double  maxcompsperkey =  (log((double) N) * 2.5); 

  /* Create an STL vector of some countints, in sorted order */
  vector<countint> v;
  for(int i=0; i<N; i++) {
    //    v.push_back(i);
    v.push_back(i);
  }

  /* Create an empty instance of RST holding countint */
  BST<countint>* r = new RST<countint>();

  /* Clear the comparison counter */
  countint::clearcount();

  /* Insert the data items, in order */
  cout << "Inserting " << N << " sorted keys in initially empty RST...";
  vector<countint>::iterator vit = v.begin();
  vector<countint>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
     // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<BST<countint>::iterator,bool> pr = r->insert(*vit);
	//r->print();
    if(! pr.second ) {
      cout << "Incorrect bool return value when inserting " << *vit << endl;
	  cin.get();
      return -1;
    }
    countint rc = *(pr.first);
    countint bc = *vit;
    if(rc < bc || bc < rc) {
      cout << "Incorrect iterator return value when inserting " << *vit << endl;
	  cin.get();
      return -1;
    }  
  }
  
  cout << " done." << endl;
  
  //  r->inorder();

  /* How many comparisons did it take to do the inserts, avg per key? */
  cout << "Max comps = " << maxcompsperkey << endl;
  double compsperkey =  countint::getcount() / (double) N;
  cout << "That took " << compsperkey << " average comparisons per key, ";
  if(compsperkey <= maxcompsperkey) cout << "OK. " << endl;
  else if (compsperkey <= maxcompsperkey * 2) cout << "could be better... " << endl;
  else {
    cout << "way too many!" << endl;
	cin.get();
    return -1;
  }

  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v.begin();
  BST<countint>::iterator en = r->end();
  BST<countint>::iterator it = r->begin();
  int i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    countint rc = *it;
    countint bc = *vit;
    if(rc < bc || bc < rc) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
	  cin.get();
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
	cin.get();
    return -1;
  }
  cout << " OK." << endl;
  cin.get();
  return 0;
}
