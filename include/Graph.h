#ifndef GRAPH_H
#define GRAPH_H

#include "arguments.h"
#include "headers.h"

class Graph {
   public:
    std::bitset<BITSIZE> *Nei;
    int N, M;

    int *deg;
    int maxDeg;

    Graph(int, int);  // init with the number of vertices and the number of edges
    void addEdge(int &, int &);  // add an edge from u to v

    ~Graph();
};

#endif