#include "..\include\Solve.h"

Solve::Solve(Graph *g) { G = g; }

Solve::~Solve() { delete G; }

void Solve::searching() {
    setVmC();
    setC();
    dfs();
}

void Solve::setVmC() {
    for (int v = 1; v <= G->N; ++v) VmC.set(v);
}

void Solve::setC() {
    for (int v = 1; v <= G->N; ++v) C.reset(v);
}

void Solve::dfs() {
    // output(C);
    std::cout << "C size: " << C.count() << std::endl;
    // std::cout << "VmC size: " << VmC.count() << std::endl;

    if (stopCheck()) {
        finalC = C;
        return;
    }

    /*-----reduction rule 1-----*/
    while (reduction1()) {
    }

    /*-----reduction rule 2-----*/

    if (reduction2()) return;

    /*-----branch rule 1-----*/
    branch1();
}

bool Solve::stopCheck() { return C.count() >= k; }

bool Solve::reduction1() {
    auto cs = C.count();

    bool flag = false;

    std::bitset<BITSIZE> T = VmC;

    for (int v = VmC._Find_first(); v < VmC.size(); v = VmC._Find_next(v)) {
        auto cap = G->Nei[v] & VmC;
        if (cap.count() < k - cs - 1) {
            flag = true;
            T.reset(v);
        }
    }
    VmC = T;
    return flag;
}

bool Solve::reduction2() {
    return VmC.count() + C.count() < k;
}

void Solve::branch1() {
    int v = VmC._Find_first();
    // std::cout << "v: " << v << std::endl;

    /*-----select v-----*/

    std::bitset<BITSIZE> VmCBefore = VmC;
    VmC = VmC & G->Nei[v];
    C.set(v);

    dfs();

    C.reset(v);
    VmC = VmCBefore;

    /*-----delete v-----*/

    VmC.reset(v);
    dfs();
    VmC.set(v);
}

void Solve::output(std::bitset<BITSIZE> &B) {
    std::cout << "---------" << std::endl;
    for (int v = B._Find_first(); v < B.size(); v = B._Find_next(v)) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}