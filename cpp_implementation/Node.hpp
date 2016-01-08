#ifndef NODE
#define NODE

#include <vector>
#include <string>
#include <armadillo>
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
  arma::fmat w_coef;
  arma::fmat w_abs;
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
  void set_w_coef(arma::fmat w);
  arma::fmat* get_w_coef();
  arma::fmat* get_w_abs();
  void print();
};

#endif
