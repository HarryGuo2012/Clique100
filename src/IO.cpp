#include "../include/IO.h"

IO::IO() {

}

void IO::input(Graph *&G, std::string inputFile, bool edgeTag) {
	edgeTag = true;
	std::ifstream fin(inputFile.c_str());

	int N, M, u, v;

	fin >> N >> M;

	G = new Graph(N, M);

	if (edgeTag) {
		for (int i = 1; i <= M; ++ i) {
			fin >> u >> v;
			G -> addEdge(u, v, i);
			G -> addEdge(v, u, i);
		}
	}
	else {
		for (int i = 1; i <= M; ++ i) {
			fin >> u >> v;
			G -> addEdge(u, v);
			G -> addEdge(v, u);
		}
	}

	//printf("%d\n", G -> N);

	fin.close();
}