#include <vector>
#include <stack>
#include "Graph.hpp"
#include "Edge.hpp"
#include "Node.hpp"
#include "enum.hpp"


//----------------------//
// access & build graph //
//----------------------//

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

Node* Graph::get_node_by_id_seq(int id) {
  // assumes that for every node n, n.id = position of n in nodes
  // (depends on how the graph has been constructed)
  return nodes.at(id);
}

Edge* Graph::add_edge(int id_x, int id_y, int color, float value) {
  Node* x = get_node_by_id(id_x);
  Node* y = get_node_by_id(id_y);
  if(x && y) {
    Edge* e = new Edge(x, y, color, value);
    edges.push_back(e);
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


//------------------//
// basic algorithms //
//------------------//

// standard recursive DFS to print the graph
void Graph::print_DFS() {
  reset_nodes();
  std::vector<Node*>::iterator it = nodes.begin();
  for(; it != nodes.end(); ++it) {
    if((*it)->get_state() == WHITE)
      print_DFS_aux(*it);
  }
}

// auxiliary DFS function
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

// find source nodes
void Graph::compute_sources() {
  std::vector<Node*>::iterator it = nodes.begin();
  while(it != nodes.end()) {
    if((*it)->get_deg_in() == 0)
      sources.push_back(*it);
    ++ it;
  }
}


//---------------------//
// relevant algorithms //
//---------------------//

// compute proper ancestors + source ancestors + edge boundary
void Graph::compute_ancestors_boundary(Edge* e) {
  reset_nodes();
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
      if(! (*it1)->is_equal(e)) {
        (*it1)->set_is_ancestor(true); // tag as ancestor for boundary calculation
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
  // for each visited nodes, pick up out edges that are not tagged as ancestors
  std::vector<Edge*>* boundary = e->get_boundary();
  std::vector<Node*>::iterator it3 = nodes.begin();
  for(; it3 != nodes.end(); ++it3) {
    if((*it3)->get_state() == BLACK) {
      std::vector<Edge*>* edges_out = (*it3)->get_edges_out();
      std::vector<Edge*>::iterator it4 = edges_out->begin();
      for(; it4 != edges_out->end(); ++it4) {
        if(! (*it4)->get_is_ancestor())
          boundary->push_back(*it4);
      }
    }
  }
}

// boundary cancellation for the acyclic case, returns the source decomposition
std::vector<float> Graph::cancel_boundary_acyclic(Edge* e) {
  std::vector<float> init_values;
  std::vector<Edge*>* a = e->get_source_ancestors();
  for(int i = 0; i < a->size(); i++)
    init_values.push_back(a->at(i)->get_value());

  std::vector<Edge*>::iterator it = e->get_boundary()->begin();
  for(; it != e->get_boundary()->end(); ++it) {
    if(! (*it)->is_equal(e))
      update_acyclic((*it), 0.);
  }

  std::vector<float> c;
  for(int i = 0; i < a->size(); i++)
    c.push_back(a->at(i)->get_value() / init_values.at(i));

  return c;
}

// propagate the cancellation of a boundary edge in terms of conversion matrices
void Graph::update_acyclic(Edge* e, float new_value) {
  float old_value = e->get_value();
  e->set_value(new_value);
  Node* n = e->get_x();
  if(n->get_deg_in() > 0) {
    arma::fmat* w_coef = n->get_w_coef();
    arma::fmat* w_abs = n->get_w_abs();
    std::vector<Edge*>* edges_in = n->get_edges_in();
    std::vector<Edge*>* edges_out = n->get_edges_out();
    float coef_old_new = new_value/old_value;
    std::vector<float> ei_new_values(n->get_deg_in());
    std::vector<Edge*>::iterator it = edges_in->begin();
    for(; it != edges_in->end(); ++it) {
      int i = e->get_num_out();
      int j = (*it)->get_num_in();
      float new_abs = (*w_abs)(i, j) * coef_old_new;
      ei_new_values.at(j) = (*it)->get_value() - (*w_abs)(i, j) + new_abs;
      (*w_abs)(i, j) = new_abs;
    }
    std::vector<Edge*>::iterator it1 = edges_out->begin();
    std::vector<Edge*>::iterator it2;
    for(; it1 != edges_out->end(); ++it1) {
      for(it2 = edges_in->begin(); it2 != edges_in->end(); ++it2) {
        int i = (*it1)->get_num_out();
        int j = (*it2)->get_num_in();
        (*w_coef)(i, j) = (*w_abs)(i, j) / ei_new_values.at(j);
      }
    }
    for(it = edges_in->begin(); it != edges_in->end(); ++it)
      update_acyclic((*it), ei_new_values.at((*it)->get_num_in()));
  }
}


//-------//
// utils //
//-------//

// reset nodes states to WHITE (unvisited)
void Graph::reset_nodes() {
  std::vector<Node*>::iterator it = nodes.begin();
  while(it != nodes.end()) {
    (*it)->set_state(WHITE);
    ++ it;
  }
}

// print any vector<Node*>
void Graph::print_nodes_vec(std::vector<Node*>* v) {
  std::vector<Node*>::iterator it = v->begin();
  for(; it != v->end(); ++it)
    (*it)->print();
}

// print any vector<Edge*>
void Graph::print_edges_vec(std::vector<Edge*>* v) {
  std::vector<Edge*>::iterator it = v->begin();
  for(; it != v->end(); ++it)
    (*it)->print();
}

// print any vector<float>
void Graph::print_float_vec(std::vector<float>* v) {
  std::vector<float>::iterator it = v->begin();
  for(; it != v->end(); ++it)
    printf("%f; ", *it);
  printf("\n");
}
