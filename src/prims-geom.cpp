#include "prims.hpp"
#include "graphDisplay.hpp"
#include <fstream>
#include <string>
#include <chrono>

constexpr int Nodes{7343};

template <typename T>
Graph<T> generateGraph()
{
    std::ifstream f{"../geom.csv"};
    std::string temp;

    Graph<T> g{};
    if (f.is_open())
    {
        for (int i = 0; i < Nodes; ++i)
        {
            getline(f, temp);
            g.addVertex(temp.substr(0, temp.find(',')));
        }
        while (getline(f, temp))
        {
            auto it = temp.find(',');
            std::string first = temp.substr(0, it);
            std::string second = temp.substr(it + 1, temp.find(','));
            int weight = std::stoi(temp.substr(temp.find_last_of(',') + 1));
            g.addEdge(first, second, weight);
            g.addEdge(second, first, weight);
        }
        // Sparse graph, need to make sure all nodes are connected
        for (int i = 2; i < Nodes + 1; ++i)
        {
            g.addEdge("1", std::to_string(i), 100);
        }
    }
    else
    {
        std::cout << "unable to open file";
        return Graph<T>{};
    }
    f.close();
    return g;
}

using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
    Graph g = generateGraph<int>();
    auto graphGeneration = high_resolution_clock::now();
    g = PrimsMST(g);
    auto end = high_resolution_clock::now();

    auto generateTime = duration_cast<milliseconds>(graphGeneration - start);
    auto totalTime = duration_cast<milliseconds>(end - start);
    auto primsTime = duration_cast<milliseconds>(end - graphGeneration);

    std::cout << "Overall Time: " << totalTime.count() << "ms\nGeneration Time: " << generateTime.count() << "ms\nPrims Time: " << primsTime.count() << "ms\n";
}
