#include "..\include\Solve.h"

Solve::Solve(Graph *g) {
    G = g;
    color = new int[G->N + 1];
    countColorTable = new int[G->N + 1];
}

Solve::~Solve() {
    delete G;
    delete[] color;
    delete[] countColorTable;
}

void Solve::searching() {
    setVmC();
    setC();
    setColor();
    stopFlag = false;
    dfs();
}

void Solve::setVmC() {
    for (int v = 1; v <= G->N; ++v) VmC.set(v);
}

void Solve::setC() {
    for (int v = 1; v <= G->N; ++v) C.reset(v);
}

void Solve::setColor() {
    for (int v = 1; v <= G->N; ++v) color[v] = countColorTable[v] = 0;
    static std::vector<int> tmpColor;
    for (int v = 1; v <= G->N; ++v) {
        tmpColor.clear();
        for (int u = G->Nei[v]._Find_first(); u < G->Nei[v].size();
             u = G->Nei[v]._Find_next(u)) {
            if (color[u]) tmpColor.push_back(color[u]);
        }
        std::sort(tmpColor.begin(), tmpColor.end());
        auto it = std::unique(tmpColor.begin(), tmpColor.end());
        tmpColor.resize(it - tmpColor.begin());

        int c = 1;
        for (auto nc : tmpColor) {
            if (nc != c) break;
            ++c;
        }
        color[v] = c;
    }
}

void Solve::dfs() {
    // output(C);
    // std::cout << "----------" << std::endl;
    // std::cout << "C size: " << C.count() << std::endl;
    // std::cout << "VmC size: " << VmC.count() << std::endl;
    // std::cout << "VmC size: " << VmC.count() << std::endl;

    if (stopFlag) return;

    if (C.count() > finalC.count()) {
        finalC = C;
        std::cout << "FinalC size: " << finalC.count() << std::endl;
    }

    if (stopCheck()) {
        finalC = C;
        stopFlag = true;
        return;
    }

    /*-----reduction rule 1-----*/
    while (reduction1()) {
    }

    /*-----reduction rule 2-----*/

    if (reduction2()) return;

    /*-----reduction rule 3-----*/

    if (reduction3()) return;

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

bool Solve::reduction2() { return VmC.count() + C.count() < k; }

bool Solve::reduction3() {
    int cnt = 0;
    for (int v = VmC._Find_first(); v < VmC.size(); v = VmC._Find_next(v)) {
        auto &c = color[v];
        if (countColorTable[c] == 0) ++cnt;
        ++countColorTable[c];
    }
    for (int v = VmC._Find_first(); v < VmC.size(); v = VmC._Find_next(v)) {
        auto &c = color[v];
        --countColorTable[c];
    }
    // std::cout << "color: " << cnt << std::endl;
    return cnt + C.count() < k;
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