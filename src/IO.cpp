#include "../include/IO.h"

IO::IO() {}

void IO::input(Graph *&G, std::string inputFile, bool edgeTag) {
    edgeTag = true;
    std::ifstream fin(inputFile.c_str());

    int N, M, u, v;
    std::string tmp1, tmp2;

    fin >> tmp1 >> tmp2 >> N >> M;

    G = new Graph(N, M);

    if (edgeTag) {
        for (int i = 1; i <= M; ++i) {
            fin >> tmp1 >> u >> v;
            G->addEdge(u, v, i);
            G->addEdge(v, u, i);
        }
    } else {
        for (int i = 1; i <= M; ++i) {
            fin >> tmp1 >> u >> v;
            G->addEdge(u, v);
            G->addEdge(v, u);
        }
    }

    // printf("%d\n", G -> N);

    fin.close();
}