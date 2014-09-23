#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <iostream>

/** A class, instances of which are vetices in an graph.
 *  Author: Evan Carey (cs100vbg)
 */
class Vertex {
private:
  std::string data; // name of the vertex

public:
  friend class Graph; // allow Graph class to access data

  /** Constructor */
  Vertex(std::string d) : data(d) {}

  /** Copy Constructor */
  Vertex(Vertex& v) : data(v.data) {}

  /** Destructor */
  virtual ~Vertex() {}

  /** Overloaded operators */
  bool operator==(const Vertex& v) const;
  bool operator!=(const Vertex& v) const;
  Vertex& operator=(const Vertex& v);

  std::string operator*() const { return data; }

  friend std::ostream& operator<<(std::ostream& out, const Vertex& v);

};

#endif // VERTEX_HPP
