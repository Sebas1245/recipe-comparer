#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "edge.h"

void edge_new(struct edge *new_edge, const char *source, const char *dest,
              double weight)
{
    set_source(new_edge, source);
    set_dest(new_edge, dest);
    set_weight(new_edge, weight);
}

void set_source(struct edge *edge, const char *source) {
    edge->source = strdup(source);
}
void set_dest(struct edge *edge, const char *dest){
    edge->dest = strdup(dest);
}
void set_weight(struct edge *edge, double weight) {
    edge->weight = weight;
}

void delete_edge(struct edge *edge) {
    free(edge->source);
    free(edge->dest);
    free(edge);
}

void print_edge(struct edge *edge) {
    printf("Printing edge...\n");
    printf("Source: %s\n", edge->source);
    printf("Destination: %s\n", edge->dest);
    printf("Weight: %f\n", edge->weight);
}