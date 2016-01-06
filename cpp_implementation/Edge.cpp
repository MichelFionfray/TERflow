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
}

State Edge::get_state() {
  return state;
}

void Edge::set_state(State s) {
  state = s;
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

void Edge::print() {
  printf("Edge from %d to %d, color = %d, value = %f\n",
         x->get_id(), y->get_id(), color, value);
}
