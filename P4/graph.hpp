#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <queue>
#include <vector>
#include <set>
#include <limits>
#include "edge.hpp"
#include "vertex.hpp"

#define DEBUG 1 // for debugging

/** A Graph class.
 *  Author: Evan Carey (cs100vbg)
 */
class Graph {
private:
  std::vector<Vertex*> vertices;
  std::vector<Edge*> edges;
    
public:
  /** Constructors */
  Graph() {}
  Graph(std::vector<Vertex*> v, std::vector<Edge*> e) : vertices(v), edges(e) {}
  Graph(const Graph& g) : vertices(g.vertices), edges(g.edges) {}

  /** Destructor */
  virtual ~Graph();

  /** Functions to add a vertex to the graph */
  Vertex* addVertex(std::string data);
  bool addVertex(Vertex* v);

  /** Functions to add an edge to the graph */
  Edge* addEdge(Vertex* v1, Vertex* v2, double cost, double time);
  bool addEdge(Edge* e);
  Edge* addEdge(std::string s1, std::string s2, double cost, double time);
  
  /** Calculate total cost of edges in graph */
  double getTotalCost();

  /** Constructs an MST of the graph using Kruskal's algorithm*/
  Graph* mst();

  /** Calculates the all-to-all shortest path time */
  double shortestPaths();
  Edge* getEdge(Vertex* v1, Vertex* v2);

  /** Print adjacency list of the graph (used for debugging) */
  void printAdjList();

  /** Overloaded operator */
  Graph& operator=(const Graph& g);
};

/** A Comparator class to be used in constructing a priority queue
 *  for the MST algorithm.
 */
class EdgeComp {
public:
  bool operator()(Edge*& lhs, Edge*& rhs) const {
    return *lhs > *rhs;
  }
};

#endif // GRAPH_HPP