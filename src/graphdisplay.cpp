#include <iostream>
#include <fstream>
#include <string>
#include "graph.hpp"
#include "graphDisplay.hpp"
#include <vector>

constexpr int Size{6};
constexpr int MaxEdges{3};

void dfs()
{
    Graph<int, Size, MaxEdges> g;

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

    makeGraph<int, Size, MaxEdges>(g);
    return;
}

int main(int, char *[])
{
    dfs();
    return 0;
}
