#include "graph.hpp"
#include <limits>
#include <iostream>

// Struct to hold necesary data for each vertex in the graph
template <typename T, size_t MaxEdges>
struct PrimData
{
    PrimData(std::weak_ptr<vertex<T, MaxEdges>> p, T w, bool i) : parent{p},
                                                                  weight{w},
                                                                  included{i}
    {
    }

    PrimData() : parent{},
                 weight{std::numeric_limits<T>::max()},
                 included{false}
    {
    }

    std::weak_ptr<vertex<T, MaxEdges>> parent;
    T weight;
    bool included;
};

template <typename T, size_t Size, size_t MaxEdges>
Graph<T, Size, MaxEdges> PrimsMST(const Graph<T, Size, MaxEdges> &g)
{
    Graph<T, Size, MaxEdges> ret{};
    const int vertexCount = g.getCurrentVertices();

    // Helper function to retrieve the index of a vertex v in the array a
    auto getVertexIndex = [&](const std::shared_ptr<vertex<T, MaxEdges>> &v, const std::array<std::shared_ptr<vertex<T, MaxEdges>>, Size> &a) -> int {
        for (int i = 0; i < vertexCount; ++i)
        {
            if (a.at(i) == v)
            {
                return i;
            }
        }
        return -1;
    };

    // Helper function to add vertex v to MST and update weight and parents of all adjacent vertices
    auto addVertexToMST = [&](const std::shared_ptr<vertex<T, MaxEdges>> &v,
                              const std::array<std::shared_ptr<vertex<T, MaxEdges>>, Size> &vertices,
                              std::array<PrimData<T, MaxEdges>, Size> &primData) -> void {
        for (int i = 0; i < v->currentEdges; ++i)
        {
            if (int index = getVertexIndex(v->Edges[i].v.lock(), vertices); index >= 0)
            {
                if (v->Edges[i].distance < primData[index].weight)
                {
                    primData[index].weight = v->Edges[i].distance;
                    primData[index].parent = v;
                }
            }
        }
    };

    // Passing in empty graph returns empty graph
    if (vertexCount <= 0)
    {
        return ret;
    }

    // Initialize Data
    std::array<std::shared_ptr<vertex<T, MaxEdges>>, Size> vertices{g.getVertices()};
    std::array<PrimData<T, MaxEdges>, Size> primData{};

    // Add first vertex to MST
    primData[0].weight = 0;
    primData[0].included = true;
    addVertexToMST(vertices[0], vertices, primData);

    // Initialize return graph vertices
    for (const auto &v : vertices)
    {
        ret.addVertex(v->name);
    }

    // Begin at 1 since first vertex is already included.
    for (int i = 1; i < vertexCount; ++i)
    {
        // Add smallest weight not already included
        T min = std::numeric_limits<T>::max();
        int index = -1;
        for (int i = 0; i < vertexCount; ++i)
        {
            if (primData[i].weight < min && !primData[i].included)
            {
                min = primData[i].weight;
                index = i;
            }
        }
        if (index >= 0)
        {
            addVertexToMST(vertices[index], vertices, primData);
            ret.addEdge(primData[index].parent.lock()->name, vertices[index]->name, primData[index].weight);
            primData[index].included = true;
        }
        else
        {
            std::cout << "No edge found"
                      << "\n";
        }
    }

    return ret;
}