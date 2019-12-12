#include "prims.hpp"

template <typename T, size_t Size, size_t MaxEdges>
Graph<T, Size, MaxEdges> generateGraph()
{
    Graph<T, Size, MaxEdges> g{};

    g.addVertex("Boulder");
    g.addVertex("Denver");
    g.addVertex("Cheyenne");
    g.addVertex("Fruita");
    g.addVertex("Moab");
    g.addVertex("LasVegas");

    // Duplicating all edges reverse direction as Prims works on undirected graphs
    g.addEdge("Boulder", "Denver", 5);
    g.addEdge("Boulder", "Cheyenne", 4);
    g.addEdge("Boulder", "Fruita", 6);
    g.addEdge("Fruita", "Denver", 2);
    g.addEdge("Cheyenne", "Moab", 9);
    g.addEdge("Moab", "Fruita", 6);
    g.addEdge("Moab", "LasVegas", 4);
    g.addEdge("Denver", "Boulder", 5);
    g.addEdge("Cheyenne", "Boulder", 4);
    g.addEdge("Fruita", "Boulder", 6);
    g.addEdge("Denver", "Fruita", 2);
    g.addEdge("Moab", "Cheyenne", 9);
    g.addEdge("Fruita", "Moab", 6);
    g.addEdge("Moab", "LasVegas", 4);

    return g;
}

int main()
{
    Graph<int, 6, 3> g2 = PrimsMST(generateGraph<int, 6, 3>());

    return 0;
}