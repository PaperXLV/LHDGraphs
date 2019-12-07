#include <iostream>
#include <vector>
#include "graph.hpp"

using namespace std;

template <typename T, size_t Size, size_t MaxEdges>
constexpr string_view compute()
{
	Graph<T, Size, MaxEdges> g{};

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

	return g.getVertices()[0].name;
}

int main()
{

	constexpr string_view comp = compute<int, 6, 3>();
	std::cout << comp << std::endl;
	return 1;
}
