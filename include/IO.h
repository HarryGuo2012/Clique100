#ifndef IO_H
#define IO_H

#include "Graph.h"
#include "headers.h"

class IO {
public:
	IO();
	void input(Graph *&, std::string, bool edgeTag = false);
};

#endif
