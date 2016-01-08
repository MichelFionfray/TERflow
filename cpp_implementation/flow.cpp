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
  g.add_nodes_range(1, 14);

  g.add_edge(1, 8, 0, 3.0);
  g.add_edge(1, 3, 0, 6.0);
  g.add_edge(1, 3, 0, 4.0);
  g.add_edge(2, 5, 0, 8.0);
  g.add_edge(2, 4, 0, 7.0);
  g.add_edge(2, 14, 0, 5.0);
  g.add_edge(3, 9, 0, 2.0);
  g.add_edge(3, 5, 0, 1.0);
  g.add_edge(3, 6, 0, 7.0);
  g.add_edge(4, 6, 0, 2.0);
  g.add_edge(4, 6, 0, 2.0);
  g.add_edge(4, 13, 0, 3.0);
  g.add_edge(5, 10, 0, 3.0);
  g.add_edge(5, 7, 0, 3.0);
  g.add_edge(5, 7, 0, 3.0);
  g.add_edge(6, 7, 0, 11.0);
  g.add_edge(7, 11, 0, 7.0);
  // our edge of interest :
  Edge* e = g.add_edge(7, 12, 0, 10.0);

  arma::fmat w3;
  w3 << 1./6. << 1./4. << arma::endr
     << 0.    << 1./4. << arma::endr
     << 5./6. << 2./4. << arma::endr;

  arma::fmat w4;
  w4 << 2./7. << arma::endr
     << 2./7. << arma::endr
     << 3./7. << arma::endr;

  arma::fmat w5;
  w5 << 5./16. << 1./2. << arma::endr
     << 5./16. << 1./2. << arma::endr
     << 6./16. << 0.    << arma::endr;

  arma::fmat w6;
  w6 << 1. << 1. << 1. << arma::endr;

  arma::fmat w7;
  w7 << 2./3. << 2./3. << 3./11. << arma::endr
     << 2./3. << 2./3. << 8./11. << arma::endr;

  // relevant nodes
  Node* n3 = g.get_node_by_id_seq(3-1);
  Node* n4 = g.get_node_by_id_seq(4-1);
  Node* n5 = g.get_node_by_id_seq(5-1);
  Node* n6 = g.get_node_by_id_seq(6-1);
  Node* n7 = g.get_node_by_id_seq(7-1);

  n3->set_w_coef(w3);
  n4->set_w_coef(w4);
  n5->set_w_coef(w5);
  n6->set_w_coef(w6);
  n7->set_w_coef(w7);

  g.compute_sources();
  g.compute_AB(e);

  printf("proper ancestors:\n");
  g.print_edges_vec(e->get_proper_ancestors());

  printf("boundary:\n");
  g.print_edges_vec(e->get_boundary());

  printf("source ancestors:\n");
  g.print_edges_vec(e->get_source_ancestors());

  printf("matrices:\n");
  n3->get_w_coef()->print();
  n3->print();
  printf("----------\n");
  n4->get_w_coef()->print();
  n4->get_w_abs()->print();
  printf("----------\n");
  n5->get_w_coef()->print();
  n5->get_w_abs()->print();
  printf("----------\n");
  n6->get_w_coef()->print();
  n6->get_w_abs()->print();
  printf("----------\n");
  n7->get_w_coef()->print();
  n7->get_w_abs()->print();

  printf("\nCancelling boundary edges...\n\n");
  g.cancel_boundary(e);

  printf("matrices:\n");
  n3->get_w_coef()->print();
  n3->get_w_abs()->print();
  printf("----------\n");
  n4->get_w_coef()->print();
  n4->get_w_abs()->print();
  printf("----------\n");
  n5->get_w_coef()->print();
  n5->get_w_abs()->print();
  printf("----------\n");
  n6->get_w_coef()->print();
  n6->get_w_abs()->print();
  printf("----------\n");
  n7->get_w_coef()->print();
  n7->get_w_abs()->print();
  printf("\n");

  printf("proper ancestors:\n");
  g.print_edges_vec(e->get_proper_ancestors());

  printf("boundary:\n");
  g.print_edges_vec(e->get_boundary());

  return 0;
}
