#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <limits>
#include "vertex.hpp"

/** A class, instances of which are edges in an graph.
 *  Author: Evan Carey (cs100vbg)
 */
class Edge {
private:
  Vertex* v_source; // Pointer to the source vertex of this edge
  Vertex* v_dest; // Pointer to the destination vertex of this edge
  double cost;    // The cost of the edge (in millions of dollars)
  double time;    // Weight (time it would take to send a packet over this edge)
  
public:
  
  /** Constructor */
  Edge(Vertex* v1, Vertex* v2, double c = std::numeric_limits<double>::max(), double t = std::numeric_limits<double>::max())
    : v_source(v1), v_dest(v2), cost(c), time(t) {}

  /** Copy Constructor */
  Edge(Edge& e) : v_source(e.v_source), v_dest(e.v_dest), cost(e.cost), time(e.time) {}

  /** Destructor */
  virtual ~Edge() {}

  /** Accessor function */
  double getCost();
  double getTime();
  Vertex* source();
  Vertex* dest();

  /** Overloaded operators */
  bool operator<(const Edge& other);
  bool operator>(const Edge& other);
  bool operator==(const Edge& other) const;
  bool operator!=(const Edge& other) const;
  Edge& operator=(const Edge& other);
  
  friend std::ostream& operator<<(std::ostream& out, const Edge& e);
};

/** Comparison function (used for priority queue in MST algorithm */
bool comp(Edge* one, Edge* other);

#endif // EDGE_HPP