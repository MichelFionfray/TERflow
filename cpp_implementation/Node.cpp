#include <stdio.h>
#include <vector>
#include <string>
#include "Node.hpp"
#include "Edge.hpp"
#include "enum.hpp"

Node::Node(int id) {
  this->id = id;
  deg_in = deg_out = 0;
  state = WHITE;
}

int Node::get_id() {
  return id;
}

State Node::get_state() {
  return state;
}

int Node::get_deg_in() {
  return deg_in;
}

int Node::get_deg_out() {
  return deg_out;
}

std::vector<Edge*>* Node::get_edges_in() {
  return &edges_in;
}

std::vector<Edge*>* Node::get_edges_out() {
  return &edges_out;
}

std::vector<Node*>* Node::get_children() {
  return &children;
}

std::vector<Node*>* Node::get_parents() {
  return &parents;
}

void Node::set_state(State s) {
  state = s;
}

void Node::add_edge_in(Edge* in) {
  edges_in.push_back(in);
  ++ deg_in;
  Node* parent = in->get_x();
  bool is_parent = false;
  std::vector<Node*>::iterator it = parents.begin();
  while(it != parents.end() && !is_parent) {
    is_parent = (*it)->is_equal(parent);
    ++ it;
  }
  if(!is_parent)
    parents.push_back(parent);
}

void Node::add_edge_out(Edge* out) {
  edges_out.push_back(out);
  ++ deg_out;
  Node* child = out->get_y();
  bool is_child = false;
  std::vector<Node*>::iterator it = children.begin();
  while(it != children.end() && !is_child) {
    is_child = (*it)->is_equal(child);
    ++ it;
  }
  if(!is_child)
    children.push_back(child);
}

bool Node::is_equal(Node* n) {
  return (id == n->get_id());
}

void Node::print() {
  printf("Node %d\n", id);
}
