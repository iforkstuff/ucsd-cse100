#include <fstream>
#include <iostream>
#include <string.h>
#include "graph.hpp"

using namespace std;

 /** netplan.cpp - The main file of Programming Assingment #4
  *  Author: Evan Carey (cs100vbg)
  */
int main(int argc, char** argv) {
  
  /* Create a graph, initially empty */
  Graph* G;
  G = new Graph();

  /* Open the input file for reading */
  if (argc < 2) {
    cout << "Error: No file specified." << endl;
    return -1;
  }
  ifstream in;
  in.open(argv[1]);
  if (in.fail()) {
    cout << "Error: Failed to open input stream!" << endl;
    cout << "Please check that the file \"" << argv[1] << "\" exists and try again." << endl;
    return -1;
  }
  
  /* Read lines from the input file and add appropriate vertices and edges
   * in the associated graph G.
   */
  string s1, s2;
  double cost, time;

  while (in.good()) {
    in >> s1 >> s2 >> cost >> time;
    if (!in.good()) break;
    G->addEdge(s1, s2, cost, time); // NOTE: duplicate edges are ignored, 
                                    // even if they have different costs/times
  }

  /* Close the input file */
  in.close();

  /* DEBUG - Print adjacency list */
  if (DEBUG) {
    cout << "\nAdjacency List (G):" << endl;
    G->printAdjList();
  }

  /* Compute the total cost of edges in G */
  double totalCost = G->getTotalCost();

  /* Create M, a minimum cost spanning tree of graph G */
  Graph* M = G->mst();

  /* DEBUG - Print adjacency list */
  if (DEBUG) {
    cout << "\nAdjacency List (M):" << endl;
    M->printAdjList();
  }

  /* Compute the total cost of edges in M */
  double mstCost = M->getTotalCost();
  
  /* Compute total minimum time paths for all edges in G. 
   * NOTE: If G is not connected, output message indicating so, then terminate.
   */
  double gTime = G->shortestPaths();
  if (gTime == std::numeric_limits<double>::max()) {
    cout << "Graph is not connected." << endl;
    return 0;
  }

  /* Compute total minimum time paths for all edges in M. */
  double mTime = M->shortestPaths();
  

  /* Output the total cost of edges in G */
  cout << totalCost << endl;

  /* Output the total cost of edges in M */
  cout << mstCost << endl;

  /* Output the difference between total cost of edges in G and in M. */
  cout << totalCost - mstCost << endl;

  /* Output total minimum time paths for all edges in G. */
  cout << gTime << endl;

  /* Output total minimum time paths for all edges in M. */
  cout << mTime << endl;

  /* Output the difference between them */
  cout << mTime - gTime << endl;

  /* Delete G and M */
  delete M;
  delete G;

  cin.get();
  return 0;
}
