#include "graph.hpp"

/** graph.cpp - an implementation of the Graph class
 *  Author: Evan Carey (cs100vbg)
 */


/** Destructor
 *  Clear all elements in edges and vertices vectors.
 */
Graph::~Graph() {
  std::vector<Edge*>::iterator e_it = edges.begin();
  while (e_it != edges.end()) {
    delete *e_it; // call Edge destructor
    e_it++;
  }
  edges.clear();
	
  std::vector<Vertex*>::iterator v_it = vertices.begin();
  while (v_it != vertices.end()) {
    delete *v_it; // call Vertex destructor
    v_it++;
  }
  vertices.clear();
  
}

/** Add a vertex to the graph.
 *  Create an vertex storing the string data.
 *  Call a function to check if the vertex already exists.
 *  Return NULL if it already exists, or a pointer to the new vertex otherwise.
 */
Vertex* Graph::addVertex(std::string data) {
  // create new vertex
  Vertex* v = new Vertex(data);

  if (addVertex(v)) // if it's not in the graph, add it
    return v;
  else {
    delete v; // otherwise, delete it
    v = NULL;
    return NULL;
  }
}
/** Add a new vertex v to the graph.
 *  If a comparable vertex already exists, return false.
 *  If no comparable vertex exists, add it to the graph and return true
 */
bool Graph::addVertex(Vertex* v) {
  // first check if vertex is already in the graph
  std::vector<Vertex*>::iterator it = vertices.begin();
  while (it != vertices.end()) {
    if ((**it) == *v)
      return false;
    it++;
  }
  
  // if it's not, add it to vertices
  vertices.push_back(v);
  return true;
}

/** Add an edge incident to v1 and v2 to the graph.
 *  Call a function to check if the edge already exists.
 *  Return NULL if it already exists, or a pointer to the new edge otherwise.
 */
Edge* Graph::addEdge(Vertex* v1, Vertex* v2, double cost, double time) {
  // create new edge
  Edge* e = new Edge(v1, v2, cost, time);

  if (addEdge(e)) // if it's not in the graph, add it
    return e;
  else {
    delete e; // otherwise, delete it
    e = NULL;
    return NULL;
  }
}

/** Add a new edge e to the graph.
 *  If a comparable edge already exists, return false.
 *  If no comparable edge exists, add it to the graph and return true
 */
bool Graph::addEdge(Edge* e) {
  // first check if edge is already in the graph
  std::vector<Edge*>::iterator it = edges.begin();
  while (it != edges.end()) {
    if ((**it) == *e)
      return false;
    it++;
  }
  // if it's not, add it to edges
  edges.push_back(e);
  return true;
}

/** Add an edge to the graph.
 *  Create vertices containing s1 and s2 if they don't already exist, and
 *  call a function to create a new edge incident to them with a cost and time.
 *  Return a pointer to the new edge or NULL if it already exists.
 */
Edge* Graph::addEdge(std::string s1, std::string s2, double cost, double time) {
  Vertex* v1 = NULL;
  Vertex* v2 = NULL;

  // Find vertices containing s1 and s2 in the graph
  std::vector<Vertex*>::iterator it = vertices.begin();
  while (it != vertices.end()) {
    if ((*it)->data == s1)
      v1 = (*it);
    if ((*it)->data == s2)
      v2 = (*it);
    it++;
  }

  // Add them if they're not in the graph
  if (v1 == NULL)
    v1 = addVertex(s1);
  if (v2 == NULL)
    v2 = addVertex(s2);

  // Add the edge connecting them
  return addEdge(v1, v2, cost, time);
}

/** Calculate the total cost of all edges in the graph
 */
double Graph::getTotalCost() {
  double cost = 0.0;
  std::vector<Edge*>::iterator it = edges.begin();
  while (it != edges.end()) {
    cost += (*it)->getCost();
    it++;
  }
  return cost;
}

/** An implemenation of Kruskal's algorithm to construct a minimum
 *  spanning tree.
 */
Graph* Graph::mst() {
  // Create a new graph m to be the MST of the the graph
  Graph* m = new Graph();
  
  /* Create the forest, where each tree contains a single vertex of the graph.
   * The tree in [0] will be used to store the final tree of vertices in m.
   */
  int forest_size = vertices.size();
  std::vector<std::set<Vertex*> > v_prime(forest_size);
  int i = 0;
  for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    v_prime[i].insert(*it);
    i++;
  }

  // Create a priority queue that contains all the edges in the graph
  std::priority_queue<Edge*, std::vector<Edge*>, EdgeComp> edgeQueue;
  std::vector<Edge*>::iterator p = edges.begin();
  while (p != edges.end()) {
    edgeQueue.push(*p);
    p++;
  }

  /* Loop while the queue is not empty and the number of vertices in m
   * is less than the number of vertices in the graph
   */
  while (!edgeQueue.empty() && v_prime[0].size() < vertices.size()) {
    // remove the edge with the least cost from the queue
    Edge* e = edgeQueue.top();

    bool found_u = false;
    bool found_v = false;
    int u_index = -1;
    int v_index = -1;

    // Find the vertices connected by the edge
    std::set<Vertex*>::iterator u_it, v_it;
    for (unsigned int i = 0; i < v_prime.size(); i++) {
      u_it = v_prime[i].find(e->source());
      v_it = v_prime[i].find(e->dest());
      if (!found_u && u_it != v_prime[i].end()) {
        found_u = true;
        u_index = i;
      }
      if (!found_v && v_it != v_prime[i].end()) {
        found_v = true;
        v_index = i;
      }
    }

    // If the vertices are in different trees, combine them into a single tree
    if ((found_u && found_v) && u_index != v_index) {

      if (u_index < v_index) {
        for (v_it = v_prime[v_index].begin(); v_it != v_prime[v_index].end(); v_it++) {
          v_prime[u_index].insert(*v_it);
        }
        v_prime[v_index].clear();
      } else {
        for (u_it = v_prime[u_index].begin(); u_it != v_prime[u_index].end(); u_it++) {
          v_prime[v_index].insert(*u_it);
        }
        v_prime[u_index].clear();
      }

      // Add the edge to the MST
      m->addEdge(e->source()->data, e->dest()->data, e->getCost(), e->getTime());
    }
    // Discard the edge
    edgeQueue.pop();
  }

  // Return the MST
  return m;
}

/** An implementation of Floyd-Warshall's algorithm to calculate the
 *  all-to-all shortest path time
 */
double Graph::shortestPaths() {
  // create distance matrix
  int num_verts = vertices.size();
  double** weights = new double*[num_verts];
  for (int i = 0; i < num_verts; ++i)
    weights[i] = new double[num_verts];

  // insert distances into matrix
  int x = 0;
  for (std::vector<Vertex*>::iterator it1 = vertices.begin(); it1 != vertices.end(); it1++) {
    int y = 0;
    for (std::vector<Vertex*>::iterator it2 = vertices.begin(); it2 != vertices.end(); it2++) {
      Edge* e = getEdge(*it1, *it2);
      if (e)
        weights[x][y] = e->getTime();
      else if (*it1 == *it2)
        weights[x][y] = 0.0; // set distance from a vertex to itself to 0
      else
        weights[x][y] = std::numeric_limits<double>::max();
      y++;
    }
    x++;
  }

  // Insert shortest paths into matrix using Floyd-Warshall's
  for (int i = 0; i < num_verts; i++) {
    for (int j = 0; j < num_verts; j++) {
      for (int k = 0; k < num_verts; k++) {
        if (weights[j][k] > weights[j][i] + weights[i][k]) {
          weights[j][k] = weights[j][i] + weights[i][k];
        }
      }
    }
  }

  // DEBUG - Prints out final distance matrix
  if (DEBUG) {
    for (int i = 0; i < num_verts; i++) {
      for (int j = 0; j < num_verts; j++) 
        std::cout << weights[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  

  // Compute total shortest path times
  double time = 0.0;
  for (int i = 0; i < num_verts; i++) {
    for (int j = 0; j < num_verts; j++) {
        time += weights[i][j];
    }
  }

  // Delete matrix
  for (int i = 0; i < num_verts; i++)
    delete [] weights[i];
  delete [] weights;

  // Return the total shortest path times
  return time;
}

/** Returns a pointer to the edge connecting v1 and v2, if it exists, or NULL otherwise */
Edge* Graph::getEdge(Vertex* v1, Vertex* v2) {
  for (std::vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    if ((*it)->source() == v1 && (*it)->dest() == v2) {
      return *it;
    }
    if ((*it)->source() == v2 && (*it)->dest() == v1) {
      return *it;
    }
  }
  return NULL;
}

/** Print adjacency list of the graph (used for debugging) */
void Graph::printAdjList() {
  std::vector<Vertex*>::iterator v_it = vertices.begin();
  while (v_it != vertices.end()) {
    std::cout << *(*v_it);
    std::vector<Edge*>::iterator e_it = edges.begin();
    while(e_it != edges.end()) {
      if ((*v_it) == (*e_it)->source())
        std::cout << " --" << *(*e_it) << "-->" << *((*e_it)->dest());
      if ((*v_it) == (*e_it)->dest())
        std::cout << " --" << *(*e_it) << "-->" << *((*e_it)->source());
      e_it++;
    }
    std::cout << std::endl;
    v_it++;
  }
}

/** Overloaded assignment operator */
Graph& Graph::operator=(const Graph& g) {
  vertices = g.vertices;
  edges = g.edges;
  return *this;
}
