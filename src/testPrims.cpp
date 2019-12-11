#include "prims.hpp"

template <typename T, size_t Size, size_t MaxEdges>
constexpr Graph<T, Size, MaxEdges> generateGraph()
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

    return g;
}

int main()
{
    constexpr Graph<int, 6, 3> g2 = PrimsMST(generateGraph<int, 6, 3>());

    return 0;
}