#include <iostream>
#include <vector>
#include "graph.hpp"

#define N 6

using namespace std;

int main()
{

	Graph<int, 6, 3> g;

	g.addVertex("Boulder");
	g.addVertex("Denver");
	g.addVertex("Cheyenne");
	g.addVertex("Fruita");
	g.addVertex("Moab");
	g.addVertex("Las Vegas");

	g.addEdge("Boulder", "Denver", 5);
	g.addEdge("Boulder", "Cheyenne", 4);
	g.addEdge("Boulder", "Fruita", 6);
	g.addEdge("Fruita", "Denver", 2);
	g.addEdge("Cheyenne", "Moab", 9);
	g.addEdge("Moab", "Fruita", 6);
	g.addEdge("Las Vegas", "Moab", 4);

	g.addEdge("Denver", "Boulder", 5);

	//g.displayEdges();
	g.adjListToMat();

	return 0;
}
