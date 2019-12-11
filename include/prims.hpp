#include "graph.hpp"
#include <limits>
#include <iostream>

template <typename T, size_t Size, size_t MaxEdges>
Graph<T, Size, MaxEdges> PrimsMST(const Graph<T, Size, MaxEdges> &g)
{
    const int vertexCount = g.getCurrentVertices();

    auto getVertexIndex = [&](const vertex<T, MaxEdges> &v, const std::array<vertex<T, MaxEdges>, Size> &a) {
        for (int i = 0; i < vertexCount; ++i)
        {
            if (a.at(i) == v)
            {
                return i;
            }
        }
        return -1;
    };

    auto addVertexToMST = [&](const vertex<T, MaxEdges> &v,
                              std::array<vertex<T, MaxEdges>, Size> &includedVertices,
                              const std::array<vertex<T, MaxEdges>, Size> &vertices,
                              std::array<T, Size> &edges) {
        for (int i = 0; i < v.currentEdges; ++i)
        {
            if (int index = getVertexIndex(*v.Edges[i].v, vertices); index >= 0)
            {
                edges[index] = std::min(v.Edges[i].distance, edges[index]);
            }
        }
        if (int index = getVertexIndex(v, vertices); index >= 0)
        {
            includedVertices[index] = v;
        }
    };

    if (vertexCount <= 0)
    {
        // Probably need some other default return;
        return Graph<T, Size, MaxEdges>{};
    }

    auto vertices = g.getVertices();

    std::array<vertex<T, MaxEdges>, Size>
        includedVertices{};

    // Initialize array of current max edge weights to determine when to add edges
    std::array<T, Size> cutEdge{};
    for (T &weight : cutEdge)
    {
        weight = std::numeric_limits<T>::max();
    }

    std::array<bool, Size> included{};
    for (bool &val : included)
    {
        val = false;
    }
    cutEdge[0] = 0;
    int currentIncluded = 1;
    included[0] = true;

    addVertexToMST(vertices[0], includedVertices, vertices, cutEdge);

    for (; currentIncluded < vertexCount; ++currentIncluded)
    {
        // Add smallest weight not already included
        T min = std::numeric_limits<T>::max();
        int index = -1;
        for (int i = 0; i < vertexCount; ++i)
        {
            if (cutEdge[i] < min && (!included[i]))
            {
                min = cutEdge[i];
                index = i;
            }
        }
        if (index >= 0)
        {
            addVertexToMST(vertices[index], includedVertices, vertices, cutEdge);
            included[index] = true;
        }
    }

    return Graph<T, Size, MaxEdges>{};
}