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

    int *color;
    int *countColorTable;

    bool stopFlag;

    void setVmC();
    void setC();
    void setColor();

    void dfs();

    bool stopCheck();

    bool reduction1();
    bool reduction2();
    bool reduction3();

    void branch1();

    void output(std::bitset<BITSIZE> &);
};

#endif