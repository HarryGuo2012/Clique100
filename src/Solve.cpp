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
    dfs(VmC, C);

    std::cout << "FinalC size: " << finalC.count() << std::endl;
    output(finalC);
}

void Solve::setVmC() {
    for (int v = 0; v < BITSIZE; ++v) VmC.reset(v);
    for (int v = 1; v <= G->N; ++v) VmC.set(v);
}

void Solve::setC() {
    for (int v = 0; v < BITSIZE; ++v) C.reset(v);
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

void Solve::dfs(std::bitset<BITSIZE> vmc, std::bitset<BITSIZE> c) {
    // output(C);
    // std::cout << "----------" << std::endl;
    // std::cout << "C size: " << C.count() << std::endl;
    // std::cout << "VmC size: " << VmC.count() << std::endl;
    // std::cout << "VmC size: " << VmC.count() << std::endl;

    if (stopFlag) return;

    // if (c.count() > finalC.count()) {
    //     finalC = c;
    //     // std::cout << "FinalC size: " << finalC.count() << std::endl;
    // }

    if (stopCheck(c)) {
        std::cout << "haha" << std::endl;
        finalC = c;
        stopFlag = true;
        return;
    }

    /*-----reduction rule 1-----*/
    while (reduction1(vmc, c)) {
    }

    /*-----reduction rule 2-----*/

    if (reduction2(vmc, c)) return;

    /*-----reduction rule 3-----*/

    if (reduction3(vmc, c)) return;

    /*-----branch rule 1-----*/
    branch1(vmc, c);
}

bool Solve::stopCheck(std::bitset<BITSIZE> &c) { return c.count() >= k; }

bool Solve::reduction1(std::bitset<BITSIZE> &vmc, std::bitset<BITSIZE> &c) {
    auto cs = c.count();

    bool flag = false;

    std::bitset<BITSIZE> T = vmc;

    for (int v = vmc._Find_first(); v < vmc.size(); v = vmc._Find_next(v)) {
        auto cap = G->Nei[v] & vmc;
        if (cap.count() < k - cs - 1) {
            flag = true;
            T.reset(v);
        }
    }
    vmc = T;
    return flag;
}

bool Solve::reduction2(std::bitset<BITSIZE> &vmc, std::bitset<BITSIZE> &c) {
    return vmc.count() + c.count() < k;
}

bool Solve::reduction3(std::bitset<BITSIZE> &vmc, std::bitset<BITSIZE> &c) {
    int cnt = 0;
    for (int v = vmc._Find_first(); v < vmc.size(); v = vmc._Find_next(v)) {
        auto &col = color[v];
        if (countColorTable[col] == 0) ++cnt;
        ++countColorTable[col];
    }
    for (int v = vmc._Find_first(); v < vmc.size(); v = vmc._Find_next(v)) {
        auto &col = color[v];
        --countColorTable[col];
    }
    // std::cout << "color: " << cnt << std::endl;
    return cnt + c.count() < k;
}

void Solve::branch1(std::bitset<BITSIZE> &vmc, std::bitset<BITSIZE> &c) {
    int v = pickV(vmc);
    // std::cout << "v: " << v << std::endl;
#pragma omp parallel sections
    {
#pragma omp section
        {
            /*-----select v-----*/

            std::bitset<BITSIZE> VmCBefore = vmc;
            vmc = vmc & G->Nei[v];
            c.set(v);

            dfs(vmc, c);

            c.reset(v);
            vmc = VmCBefore;
        }

#pragma omp section
        {
            /*-----delete v-----*/

            vmc.reset(v);
            dfs(vmc, c);
            vmc.set(v);
        }
    }
}

int Solve::pickV(std::bitset<BITSIZE> &vmc) {
    int maxDeg = 0, maxV;
    for (int v = vmc._Find_first(); v < vmc.size(); v = vmc._Find_next(v)) {
        auto cap = G->Nei[v] & vmc;
        if (cap.count() > maxDeg) {
            maxDeg = cap.count(), maxV = v;
        }
    }
    return maxV;
}

void Solve::output(std::bitset<BITSIZE> &B) {
    std::cout << "---------" << std::endl;
    for (int v = B._Find_first(); v < B.size(); v = B._Find_next(v)) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}