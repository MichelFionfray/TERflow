#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <armadillo>
#include "Graph.hpp"
#include "Edge.hpp"
#include "Node.hpp"

int main() {
  Graph g;

  g.add_nodes_range(0,5);

  g.add_edge(0, 1, 0, 4.0);
  g.add_edge(0, 1, 1, 5.0);
  g.add_edge(0, 2, 0, 3.0);
  g.add_edge(0, 2, 1, 2.0);
  g.add_edge(1, 3, 0, 6.0);
  g.add_edge(1, 4, 0, 3.0);
  g.add_edge(3, 4, 0, 2.0);
  g.add_edge(4, 2, 0, 9.0);
  Edge* e = g.add_edge(3, 4, 1, 4.0);

/* cyclic
  g.add_edge(0, 1, 0, 4.0);
  g.add_edge(0, 1, 1, 5.0);
  g.add_edge(0, 2, 0, 3.0);
  g.add_edge(0, 2, 1, 2.0);
  g.add_edge(1, 3, 0, 6.0);
  g.add_edge(1, 4, 0, 3.0);
  g.add_edge(3, 4, 0, 2.0);
  g.add_edge(4, 2, 0, 7.0);
  g.add_edge(4, 1, 0, 2.0);
  Edge* e = g.add_edge(3, 4, 1, 4.0);
*/

  arma::fmat w1;
  w1 << 3./4. << 3./5. << arma::endr
     << 1./4. << 2./5. << arma::endr;

  arma::fmat w3;
  w3 << 2./6. << arma::endr
     << 4./6. << arma::endr;

  arma::fmat w4;
  w4 << 1. << 1. << 1. << arma::endr;

  Node* n1 = g.get_node_by_id_seq(1);
  Node* n3 = g.get_node_by_id_seq(3);
  Node* n4 = g.get_node_by_id_seq(4);

  n1->set_w_coef(w1);
  n3->set_w_coef(w3);
  n4->set_w_coef(w4);

  g.compute_sources();
  g.compute_ancestors_boundary(e);

  printf("Cancelling boundary edges...\n");
  std::vector<float> c = g.cancel_boundary_acyclic(e);
  printf("\n");

  printf("Updated edges:\n");
  g.print_edges_vec(g.get_edges());
  printf("\n");

  printf("source edges:\n");
  g.print_edges_vec(e->get_source_ancestors());
  printf("\n");

  printf("respective decomposition:\n");
  g.print_float_vec(&c);

  return 0;
}
