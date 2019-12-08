#include <iostream>
#include <vector>
#include "graph.hpp"

using namespace std;

int main()
{

    Graph<int, 6, 5> g;

    g.addVertex("Boulder");
    g.addVertex("Denver");
    g.addVertex("Cheyenne");
    g.addVertex("Fruita");
    g.addVertex("Moab");
    g.addVertex("Las Vegas");

    g.addEdge("Boulder", "Denver", 3);
    g.addEdge("Denver", "Cheyenne", 5);
    g.addEdge("Cheyenne", "Moab", 2);
    g.addEdge("Moab", "Las Vegas", 9);

    // long edge, shouldn't take this path
    g.addEdge("Boulder", "Las Vegas", 100);

    // vertex<int, 5> *last = g.dijkstraSearch("Boulder", "Las Vegas");
    // vertex<int, 5> *temp = last;
    // while (temp != nullptr)
    // {
    //     cout << temp->name << endl;
    //     temp = temp->dijkParent;
    // }
    g.dijkstraDisplay("Boulder", "Las Vegas");

    return 0;
}
