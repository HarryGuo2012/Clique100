#ifndef SOLVE_H
#define SOLVE_H

#include "Graph.h"
#include "arguments.h"
#include "headers.h"
#include "omp.h"

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

    void dfs(std::bitset<BITSIZE>, std::bitset<BITSIZE>);

    bool stopCheck(std::bitset<BITSIZE> &);

    bool reduction1(std::bitset<BITSIZE> &, std::bitset<BITSIZE> &);
    bool reduction2(std::bitset<BITSIZE> &, std::bitset<BITSIZE> &);
    bool reduction3(std::bitset<BITSIZE> &, std::bitset<BITSIZE> &);

    void branch1(std::bitset<BITSIZE> &, std::bitset<BITSIZE> &);

    int pickV(std::bitset<BITSIZE> &);

    void output(std::bitset<BITSIZE> &);
};

#endif