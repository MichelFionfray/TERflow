#include <stdio.h>
#include <vector>
#include <string>
#include "Edge.hpp"
#include "Node.hpp"
#include "enum.hpp"

Edge::Edge(Node* x, Node* y, int color, float value) {
  this->x = x;
  this->y = y;
  this->color = color;
  this->value = value;
  this->num_out = x->get_deg_out();
  this->num_in = y->get_deg_in();
  x->add_edge_out(this);
  y->add_edge_in(this);
  // there is a correspondance bewteen in/out nums (which serve as indices in
  // conversion matrices) and the edge position in the edge_in/out vectors of x and y.
  // thus, for example, to access the input edge of element (i,j) in w(n),
  // we can just do n.get_edges_in()->at(j)
}

bool Edge::get_is_ancestor() {
  return is_ancestor;
}

void Edge::set_is_ancestor(bool b) {
  is_ancestor = b;
}

std::vector<Edge*>* Edge::get_proper_ancestors() {
  return &proper_ancestors;
}

std::vector<Edge*>* Edge::get_boundary() {
  return &boundary;
}

std::vector<Edge*>* Edge::get_source_ancestors() {
  return &source_ancestors;
}

bool Edge::is_equal(Edge* e) {
  return (color == e->get_color() &&
          x->is_equal(e->get_x()) &&
          y->is_equal(e->get_y()));
}

Node* Edge::get_x() {
  return x;
}

Node* Edge::get_y() {
  return y;
}

int Edge::get_color() {
  return color;
}

int Edge::get_num_out() {
  return num_out;
}

int Edge::get_num_in() {
  return num_in;
}

float Edge::get_value() {
  return value;
}

void Edge::set_value(float v) {
  value = v;
}

void Edge::print() {
  printf("Edge from %d (num_out=%d) to %d (num_in=%d), color = %d, value = %f\n",
         x->get_id(), num_out, y->get_id(), num_in, color, value);
}
