#include "../include/Graph.h"

Graph::Graph(int NN, int MM) {
    N = NN;
    M = MM;
    deg = new int[N + 10];
    Nei = new std::bitset<BITSIZE>[N + 10];
}

Graph::~Graph() {
    delete[] deg;
    delete[] Nei;
}

void Graph::addEdge(int &u, int &v) {
    Nei[u].set(v);
    Nei[v].set(u);
    ++deg[u];
    if (deg[u] > maxDeg) maxDeg = deg[u];
}