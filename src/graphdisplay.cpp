#include <iostream>
#include <fstream>
#include <string>
#include "graph.hpp"
#include "graphDisplay.hpp"
#include <vector>

constexpr int Size{16};

void dispGraph()
{
    Graph<int, Size> g;

    g.addVertex("Boulder");
    g.addVertex("Denver");
    g.addVertex("Cheyenne");
    g.addVertex("Fruita");
    g.addVertex("Moab");
    g.addVertex("LasVegas");
    g.addVertex("Dallas");
    g.addVertex("SanFransisco");
    g.addVertex("Lansing");
    g.addVertex("AnnArbor");
    g.addVertex("NewYork");
    g.addVertex("Chicago");
    g.addVertex("TampaBay");
    g.addVertex("Oakland");
    g.addVertex("ColoradoSprings");
    g.addVertex("Broomfield");

    g.addEdge("Boulder", "Denver", 5);
    g.addEdge("Boulder", "Cheyenne", 4);
    g.addEdge("Boulder", "Fruita", 6);
    g.addEdge("Fruita", "Denver", 2);
    g.addEdge("Cheyenne", "Moab", 9);
    g.addEdge("Moab", "Fruita", 6);
    g.addEdge("LasVegas", "Moab", 4);
    g.addEdge("Broomfield", "Oakland", 20);
    g.addEdge("AnnArbor", "Dallas", 5);
    g.addEdge("TampaBay", "SanFransisco", 56);
    g.addEdge("Denver", "Chicago", 3);
    g.addEdge("Dallas", "NewYork", 56);
    g.addEdge("TampaBay", "Boulder", 78);
    g.addEdge("SanFransisco", "ColoradoSprings", 10);
    g.addEdge("Broomfield", "LasVegas", 1);
    g.addEdge("TampaBay", "Moab", 4);
    g.addEdge("Cheyenne", "SanFransisco", 9);
    g.addEdge("AnnArbor", "ColoradoSprings", 5);
    g.addEdge("Oakland", "Fruita", 423);
    g.addEdge("Boulder", "Oakland", 63);
    g.addEdge("ColoradoSprings", "LasVegas", 70);
    g.addEdge("Denver", "Boulder", 5);

    makeGraph<int, Size>(g);
    return;
}

template <typename T, size_t Size>
Graph<T, Size> generateGraph()
{
    Graph<T, Size> g{};

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

    return g;
}

int main(int, char *[])
{
    //dispGraph();
    Graph<int, 6> g = generateGraph<int, 6>();
    makeGraph<int, 6>(g);
    return 0;
}
