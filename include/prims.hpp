#include "graph.hpp"
#include <limits>
#include <iostream>
#include <queue>

// Struct to hold necesary data for each vertex in the graph
template <typename T>
struct PrimData
{
    PrimData(std::weak_ptr<vertex<T>> p, T w, bool i) : parent{p},
                                                        weight{w},
                                                        included{i}
    {
    }

    PrimData() = default;
    PrimData(const PrimData &) = default;
    PrimData(PrimData &&) = default;
    PrimData &operator=(const PrimData &) = default;
    PrimData &operator=(PrimData &&) = default;
    ~PrimData() = default;

    std::weak_ptr<vertex<T>> parent{};
    T weight{std::numeric_limits<T>::max()};
    bool included{false};
};

template <typename T, size_t Size>
Graph<T, Size> PrimsMST(const Graph<T, Size> &g)
{
    Graph<T, Size> ret{};
    const int vertexCount = g.getCurrentVertices();

    // Helper function to retrieve the index of a vertex v in the array a
    auto getVertexIndex = [&](const std::shared_ptr<vertex<T>> &v, const std::array<std::shared_ptr<vertex<T>>, Size> &a) -> int {
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
    auto addVertexToMST = [&](const std::shared_ptr<vertex<T>> &v,
                              const std::array<std::shared_ptr<vertex<T>>, Size> &vertices,
                              std::array<PrimData<T>, Size> &primData) -> void {
        for (int i = 0; i < v->Edges.size(); ++i)
        {
            if (int index = getVertexIndex(v->Edges[i].v.lock(), vertices); index >= 0)
            {
                if (v->Edges[i].weight < primData[index].weight)
                {
                    primData[index].weight = v->Edges[i].weight;
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
    std::array<std::shared_ptr<vertex<T>>, Size>
        vertices{g.getVertices()};
    std::array<PrimData<T>, Size> primData{};

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
        for (int j = 0; j < vertexCount; ++j)
        {
            if (primData[j].weight < min && !primData[j].included)
            {
                min = primData[j].weight;
                index = j;
            }
        }
        // Insert vertex[index] into the MST, add relevent edge to return graph
        if (index >= 0)
        {
            addVertexToMST(vertices[index], vertices, primData);
            ret.addEdge(primData[index].parent.lock()->name, vertices[index]->name, primData[index].weight);
            primData[index].included = true;
        }
        else
        {
            std::cout << "No edge found\n";
        }
    }

    return ret;
}