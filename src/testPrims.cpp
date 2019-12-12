#include "prims.hpp"
#include "graphDisplay.hpp"

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

template <typename T, size_t Size, size_t MaxEdges>
Graph<T, Size, MaxEdges> constructLargeGraph(std::string filepath = "")
{
    //filepath = (filepath == "") ? filepath : "../data-filtered.txt";
    std::ifstream fin{"../data-filtered.txt"};
    //std::cout << filepath;

    std::vector<std::vector<std::string>> graphData;
    std::vector<std::string> line;
    std::string temp, row, word;
    Graph<T, Size, MaxEdges> g;

    if (fin.is_open())
    {
        while (getline(fin, temp))
        {
            line.clear();

            std::stringstream s(temp);

            std::cout << row;

            while (getline(s, word, ','))
            {
                line.push_back(word);
            }

            graphData.push_back(line);
        }

        for (const auto &line : graphData)
        {
            std::cout << "adding vertex: " << line[0] << "\n";
            g.addVertex(line[0]);
        }
        for (int j = 0; j < graphData.size(); j++)
        {
            const auto &line = graphData[j];
            for (int i = 1; i < line.size() - 2; i++)
            {
                // stof is specialized for float, I think I need to change to more generic
                if (j != i && stof(line[i]) != 0)
                {
                    g.addEdge(line[0], g.getVertices()[i]->name, stof(line[i]));
                }
            }
        }
    }
    else
    {
        std::cout << "unable to open file" << std::endl;
    }
    return g;
}

int main()
{
    //Graph<int, 6, 3> g2 = PrimsMST(generateGraph<int, 6, 3>());
    Graph<float, 30, 29> g = PrimsMST(constructLargeGraph<float, 30, 29>());

    return 0;
}