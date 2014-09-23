#include "edge.hpp"

/** edge.cpp - an implementation of the Edge class
 *  Author: Evan Carey (cs100vbg)
 */


/** Return edge's cost */
double Edge::getCost() {
  return cost;
}

/** Return edge's time */
double Edge::getTime() {
  return time;
}

/** Return edge's source vertex */
Vertex* Edge::source() {
  if (v_source)
    return v_source;
  return 0;
}

/** Return edge's dest vertex */
Vertex* Edge::dest() {
  if (v_dest)
    return v_dest;
  return 0;
}

/** Comparison operators */
bool Edge::operator<(const Edge& other) {
  return cost < other.cost;
}
bool Edge::operator>(const Edge& other) {
  return cost > other.cost;
}

/** Equality comparison.
 *  Two edges are considered equal if they are incident to the same vertices
 */
bool Edge::operator==(const Edge& other) const {
  // Check if vertices match
  if ((v_source == other.v_source && v_dest == other.v_dest) 
    || (v_source == other.v_dest && v_dest == other.v_source))
    return true;
  return false;
}

/** Inequality comparison */
bool Edge::operator!=(const Edge& other) const {
  return !(*this == other);
}

/** Assign all data fields from other edge to this */
Edge& Edge::operator=(const Edge& other) {
  v_source = other.v_source;
  v_dest = other.v_dest;
  cost = other.cost;
  time = other.time;

  return *this;
}

/** Output edge's cost and time.
 *  Used for debugging.
 */
std::ostream& operator<<(std::ostream& out, const Edge& e) {
  out << "(" << e.cost << "," << e.time << ")";
  return out;
}

/** Comparison used for priority queue */
bool comp(Edge* one, Edge* other) {
  return *one < *other;
}