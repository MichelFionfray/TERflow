#ifndef GRAPH
#define GRAPH

#include <vector>

class Edge;
class Node;

class Graph {
private:
  std::vector<Edge*> edges;
  std::vector<Node*> nodes;
  std::vector<Node*> sources;
public:
  std::vector<Edge*>* get_edges();
  std::vector<Node*>* get_nodes();
  Node* get_node_by_id(int id);
  Node* get_node_by_id_seq(int id);
  Edge* add_edge(int id_x, int id_y, int color, float value);
  void add_node(int id);
  void add_nodes_range(int id_start, int id_end);
  void compute_AB(Edge* e);
  void cancel_boundary(Edge* e);
  void update(Edge* e, float new_value);
  void compute_sources();
  void print_DFS();
  void print_DFS_aux(Node* n);
  void reset_nodes();
  void reset_edges();
  void print_nodes_vec(std::vector<Node*>* v);
  void print_edges_vec(std::vector<Edge*>* v);
};

#endif
