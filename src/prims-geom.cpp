#include "prims.hpp"
#include <fstream>
#include <string>

constexpr int Nodes{1000};

template <typename T, size_t Size>
Graph<T, Size> generateGraph()
{
    std::ifstream f{"../geom.csv"};
    std::string temp;

    Graph<T, Size> g{};
    if (f.is_open())
    {
        std::cout << "opened\n";
        for (int i = 0; i < Size; ++i)
        {
            getline(f, temp);
            std::cout << temp.substr(0, temp.find(',')) << "\n";
            g.addVertex(temp.substr(0, temp.find(',')));
        }
        while (getline(f, temp))
        {
            auto it = temp.find(',');
            std::string first = temp.substr(0, it);
            std::string second = temp.substr(it + 1, temp.find(','));
            int weight = std::stoi(temp.substr(temp.find_last_of(',') + 1));
            g.addEdge(first, second, weight);
        }
    }
    else
    {
        std::cout << "unable to open file";
        return Graph<T, Size>{};
    }
    f.close();
    std::cout << "graph created\n";
    return Graph<T, Size>{};
}

int main()
{
    Graph g = PrimsMST(generateGraph<int, Nodes>());
}
