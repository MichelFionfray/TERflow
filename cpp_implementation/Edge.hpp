#ifndef EDGE
#define EDGE

#include <vector>
#include <string>
#include "enum.hpp"

class Node;

class Edge {
private:
  Node* x;
  Node* y;
  State state;
  int color;
  float value;
  std::vector<Edge*> proper_ancestors;
  std::vector<Edge*> boundary;
  std::vector<Edge*> source_ancestors;
public:
  Edge(Node* x, Node* y, int color, float value);
  State get_state();
  void set_state(State s);
  std::vector<Edge*>* get_proper_ancestors();
  std::vector<Edge*>* get_boundary();
  std::vector<Edge*>* get_source_ancestors();
  bool is_equal(Edge* e);
  Node* get_x();
  Node* get_y();
  int get_color();
  void print();
};

#endif
