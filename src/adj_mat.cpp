#include <iostream>
#include <vector>
#include "graph.hpp"

#define MAX_VERT 16
#define MAX_EDGES 20

using namespace std;

int main()
{

    Graph<int, MAX_VERT, MAX_EDGES> g;

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

    g.adjListToMat();

    return 0;
}
