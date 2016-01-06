#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Graph.hpp"
#include "Edge.hpp"
#include "Node.hpp"

int main() {
  Graph g;
  g.add_nodes_range(0, 4);
  g.add_edge(0, 1, 0, 0.0);
  g.add_edge(1, 0, 0, 0.0);
  g.add_edge(0, 2, 0, 0.0);
  g.add_edge(1, 2, 0, 0.0);
  g.add_edge(1, 4, 0, 0.0);
  Edge* e = g.add_edge(2, 3, 0, 0.0);
  g.add_edge(3, 0, 0, 0.0);
  g.add_node(5);
  g.add_edge(5, 0, 0, 0.0);
  g.add_edge(5, 2, 0, 0.0);
  g.add_edge(5, 4, 0, 0.0);
  g.compute_sources();
  g.compute_AB(e);
  printf("proper ancestors:\n");
  g.print_edges_vec(e->get_proper_ancestors());
  printf("boundary:\n");
  g.print_edges_vec(e->get_boundary());
  printf("source ancestors:\n");
  g.print_edges_vec(e->get_source_ancestors());
  return 0;
}
