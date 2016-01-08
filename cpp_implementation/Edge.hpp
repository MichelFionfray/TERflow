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
  int color;
  float value;
  int num_out;
  int num_in;
  bool is_ancestor;
  std::vector<Edge*> proper_ancestors;
  std::vector<Edge*> boundary;
  std::vector<Edge*> source_ancestors;
public:
  Edge(Node* x, Node* y, int color, float value);
  bool get_is_ancestor();
  void set_is_ancestor(bool b);
  std::vector<Edge*>* get_proper_ancestors();
  std::vector<Edge*>* get_boundary();
  std::vector<Edge*>* get_source_ancestors();
  bool is_equal(Edge* e);
  Node* get_x();
  Node* get_y();
  int get_color();
  int get_num_out();
  int get_num_in();
  float get_value();
  void set_value(float v);
  void print();
};

#endif
