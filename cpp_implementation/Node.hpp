#ifndef NODE
#define NODE

#include <vector>
#include <string>
#include "enum.hpp"

class Edge;

class Node {
private:
  State state;
  int id, deg_in, deg_out;
  std::vector<Edge*> edges_in;
  std::vector<Edge*> edges_out;
  std::vector<Node*> children;
  std::vector<Node*> parents;
  float* conv_mat;
public:
  Node(int id);
  int get_id();
  State get_state();
  int get_deg_in();
  int get_deg_out();
  std::vector<Edge*>* get_edges_in();
  std::vector<Edge*>* get_edges_out();
  std::vector<Node*>* get_children();
  std::vector<Node*>* get_parents();
  void set_state(State s);
  void add_edge_in(Edge* in);
  void add_edge_out(Edge* out);
  bool is_equal(Node* n);
  void print();
};

#endif
