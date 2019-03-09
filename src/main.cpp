#include "../include/IO.h"
#include "../include/Graph.h"
#include "../include/headers.h"
#include "../include/"

Graph *G;
IO io;

std::string inputFile, outputFile;

int main(int argc, char *argv[]) {
	inputFile = argv[argc - 2];
	outputFile = argv[argc - 1];
	io.input(G, inputFile);

	
	return 0;
}