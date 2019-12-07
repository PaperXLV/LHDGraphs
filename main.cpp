#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;


int main()
{

	Graph g;

	g.addVertex("Boulder");
	g.addVertex("Denver");
	g.addVertex("Cheyenne");
	g.addVertex("Fruita");
	g.addVertex("Moab");
	g.addVertex("Las Vegas");

	g.addEdge("Boulder", "Denver");
	g.addEdge("Boulder", "Cheyenne");
	g.addEdge("Boulder", "Fruita");
	g.addEdge("Fruita", "Denver");
	g.addEdge("Cheyenne", "Moab");
	g.addEdge("Moab", "Fruita");
	g.addEdge("Las Vegas", "Moab"); 

	//g.displayEdges();

	g.breadthFirstTraverse("Fruita");

    return 0;
}
