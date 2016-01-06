#include <vector>
#include <stack>
#include "Graph.hpp"
#include "Edge.hpp"
#include "Node.hpp"
#include "enum.hpp"

std::vector<Edge*>* Graph::get_edges() {
  return &edges;
}

std::vector<Node*>* Graph::get_nodes() {
  return &nodes;
}

Node* Graph::get_node_by_id(int id) {
  std::vector<Node*>::iterator it = nodes.begin();
  while(it != nodes.end() && (*it)->get_id() != id)
    ++ it;
  if((*it)->get_id() == id)
    return *it;
  else
    return 0;
}

Edge* Graph::add_edge(int id_x, int id_y, int color, float value) {
  Node* x = get_node_by_id(id_x);
  Node* y = get_node_by_id(id_y);
  if(x && y) {
    Edge* e = new Edge(x, y, color, value);
    edges.push_back(e);
    x->add_edge_out(e);
    y->add_edge_in(e);
    return e;
  }
  else
    return 0;
}

void Graph::add_node(int id) {
  nodes.push_back(new Node(id));
}

void Graph::add_nodes_range(int id_start, int id_end) {
  for(int id = id_start; id <= id_end; id++)
    nodes.push_back(new Node(id));
}

void Graph::make_random_balanced() {
  // set random values for each edge, so that G has a balanced value
  // sets W matrix values accordingly
}

void Graph::compute_AB(Edge* e) {
  reset_nodes();
  reset_edges();
  // compute proper ancestors + source ancestors
  std::vector<Edge*>* ancestors = e->get_proper_ancestors();
  std::vector<Edge*>* source_ancestors = e->get_source_ancestors();
  std::stack<Node*> stack;
  Node* x = e->get_x();
  x->set_state(GRAY);
  stack.push(x);
  // reverse DFS from x(e)
  while(!stack.empty()) {
    Node* n = stack.top();
    stack.pop();
    std::vector<Edge*>* edges_in = n->get_edges_in();
    std::vector<Edge*>::iterator it1 = edges_in->begin();
    for(; it1 != edges_in->end(); ++it1) {
      if(!(*it1)->is_equal(e)) {
        (*it1)->set_state(BLACK); // tag as ancestor for boundary calculation
        if((*it1)->get_x()->get_deg_in() == 0) // the edge is also a source
          source_ancestors->push_back(*it1);
        ancestors->push_back(*it1);
      }
    }
    // push parent nodes on stack
    std::vector<Node*>* parents = n->get_parents();
    std::vector<Node*>::iterator it2 = parents->begin();
    for(; it2 != parents->end(); ++it2) {
      if((*it2)->get_state() == WHITE) {
        (*it2)->set_state(GRAY);
        stack.push(*it2);
      }
    }
    n->set_state(BLACK); // tag current node as visited
  }
  // compute boundary :
  // loop over visited nodes, pick up out-edges that are not tagged as ancestors
  std::vector<Edge*>* boundary = e->get_boundary();
  std::vector<Node*>::iterator it3 = nodes.begin();
  for(; it3 != nodes.end(); ++it3) {
    if((*it3)->get_state() == BLACK) {
      std::vector<Edge*>* edges_out = (*it3)->get_edges_out();
      std::vector<Edge*>::iterator it4 = edges_out->begin();
      for(; it4 != edges_out->end(); ++it4) {
        if((*it4)->get_state() != BLACK)
          boundary->push_back(*it4);
      }
    }
  }
}

void Graph::compute_sources() {
  std::vector<Node*>::iterator it = nodes.begin();
  while(it != nodes.end()) {
    if((*it)->get_deg_in() == 0)
      sources.push_back(*it);
    ++ it;
  }
}

// standard recursive DFS
void Graph::print_DFS() {
  reset_nodes();
  std::vector<Node*>::iterator it = nodes.begin();
  for(; it != nodes.end(); ++it) {
    if((*it)->get_state() == WHITE)
      print_DFS_aux(*it);
  }
}

void Graph::print_DFS_aux(Node* n) {
  n->set_state(GRAY);
  n->print();
  std::vector<Node*>* children = n->get_children();
  std::vector<Node*>::iterator it = children->begin();
  for(; it != children->end(); ++it) {
    if((*it)->get_state() == WHITE)
      print_DFS_aux(*it);
  }
  n->set_state(BLACK);
}

void Graph::reset_nodes() {
  std::vector<Node*>::iterator it = nodes.begin();
  while(it != nodes.end()) {
    (*it)->set_state(WHITE);
    ++ it;
  }
}

void Graph::reset_edges() {
  std::vector<Edge*>::iterator it = edges.begin();
  while(it != edges.end()) {
    (*it)->set_state(WHITE);
    ++ it;
  }
}

void Graph::print_nodes_vec(std::vector<Node*>* v) {
  std::vector<Node*>::iterator it = v->begin();
  for(; it != v->end(); ++it)
    (*it)->print();
}

void Graph::print_edges_vec(std::vector<Edge*>* v) {
  std::vector<Edge*>::iterator it = v->begin();
  for(; it != v->end(); ++it)
    (*it)->print();
}
