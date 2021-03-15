#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>

struct edge {
  char *source;
  char *dest;
  double weight;
};

void edge_new(struct edge *new_edge, const char* source, const char* dest,
              double weight);
void set_source(struct edge *edge, const char *source);
void set_dest(struct edge *edge, const char *dest);
void set_weight(struct edge *edge, double weight);
void delete_edge(struct edge *edge);
void print_edge(struct edge *edge);

#endif
