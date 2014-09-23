#include "vertex.hpp"

/** vertex.cpp - an implementation of the Vertex class
 *  Author: and Evan Carey (cs100vbg)
 */


/** Equality operator
 *  Return true if data fields match, false otherwise.
 */
bool Vertex::operator==(const Vertex& other) const {
  return (data.compare(other.data) == 0);
}

/** Inequality operator.
 *  Return true if data fields do not match, false otherwise.
 */
bool Vertex::operator!=(const Vertex& other) const {
  return (data.compare(other.data) != 0);
}

/** Assignment operator */
Vertex& Vertex::operator=(const Vertex& v) {
  data = v.data;
  return *this;
}

/** Output vertex's data.
 *  Used for debugging.
 */
std::ostream& operator<<(std::ostream& out, const Vertex& v) {
  out << "[" << v.data << "]";
  return out;
}