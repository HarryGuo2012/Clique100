#ifndef SOLVE_H
#define SOLVE_H

#include "Graph.h"
#include "arguments.h"
#include "headers.h"

class Solve {
   public:
    Solve(Graph *);
    ~Solve();

    std::bitset<BITSIZE> finalC;

    void searching();

   private:
    Graph *G;
    std::bitset<BITSIZE> VmC;
    std::bitset<BITSIZE> C;

    void setVmC();
    void setC();

    void dfs();

    bool stopCheck();

    bool reduction1();
    bool reduction2();

    void branch1();

    void output(std::bitset<BITSIZE> &);
};

#endif