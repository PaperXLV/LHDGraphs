#include "graphDisplay.hpp"
#include "graph.hpp"
#include "traversals.hpp"
#include "dijkstras.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

int main()
{
    std::ifstream fin("data-filtered.txt");
    //fin.open("data-filtered.txt", std::ios::in);

    std::vector<std::vector<std::string>> graphData;
    std::vector<std::string> line;
    std::string temp, row, word;
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

        Graph<float, 30, 29> g;

        for (const auto &line : graphData)
        {
            g.addVertex(line[0]);
        }
        for (int j = 0; j < graphData.size(); j++)
        {
            const auto &line = graphData[j];
            for (int i = 1; i < line.size() - 3; i++)
            {
                if (j != i)
                {
                    g.addEdge(line[0], g.getVertices()[i].name, stof(line[i]));
                }
            }
        }
        makeGraph(g);
    }
    else
    {
        std::cout << "unable to open file" << std::endl;
    }
}