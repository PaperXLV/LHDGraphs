#include "graph.hpp"
#include <limits>
#include <iostream>
#include <queue>

// Struct to hold necesary data for each vertex in the graph
template <typename T>
struct PrimData
{
    PrimData(std::shared_ptr<vertex<T>> s, std::shared_ptr<vertex<T>> p, T w) : parent{p},
                                                                                self{s},
                                                                                weight{w}
    {
    }

    PrimData() = default;
    PrimData(const PrimData &) = default;
    PrimData(PrimData &&) = default;
    PrimData &operator=(const PrimData &) = default;
    PrimData &operator=(PrimData &&) = default;
    ~PrimData() = default;

    std::shared_ptr<vertex<T>> parent{};
    std::shared_ptr<vertex<T>> self{};
    T weight{std::numeric_limits<T>::max()};
};

template <typename T>
bool operator>(const PrimData<T> &lhs, const PrimData<T> &rhs)
{
    return lhs.weight > rhs.weight;
}

template <typename T>
bool operator<(const PrimData<T> &lhs, const PrimData<T> &rhs)
{
    return lhs.weight < rhs.weight;
}

template <typename T>
bool operator==(const PrimData<T> &lhs, const PrimData<T> &rhs)
{
    return lhs.weight == rhs.weight;
}

template <typename T>
bool operator!=(const PrimData<T> &lhs, const PrimData<T> &rhs)
{
    return !(lhs.weight == rhs.weight);
}

template <typename T>
Graph<T> PrimsMST(const Graph<T> &g)
{
    Graph<T> ret{};
    const int vertexCount = g.getCurrentVertices();
    /*
    // Helper function to retrieve the index of a vertex v in the vector a
    auto getVertexIndex = [&](const std::shared_ptr<vertex<T>> &v, const std::vector<std::shared_ptr<vertex<T>>> &a) -> int {
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
                              const std::vector<std::shared_ptr<vertex<T>>> &vertices,
                              std::vector<PrimData<T>> &primData) -> void {
        if (int index = getVertexIndex(v->Edges[i].v.lock(), vertices); index >= 0)
        {
            if (v->Edges[i].weight < primData[index].weight)
            {
                primData[index].weight = v->Edges[i].weight;
                primData[index].parent = v;
            }
        }
    };
    */
    auto checkIncluded = [&](const std::shared_ptr<vertex<T>> &v, const std::vector<std::string> &included) {
        for (const auto &inc : included)
        {
            if (v->name == inc)
            {
                return true;
            }
        }
        return false;
    };

    auto addFromPriorityQueue = [&](std::priority_queue<PrimData<T>, std::vector<PrimData<T>>, std::greater<PrimData<T>>> &pq, std::vector<std::string> &included) {
        PrimData<T> top = pq.top();
        pq.pop();

        if (!checkIncluded(top.self, included))
        {
            included.push_back(top.self->name);
            if (top.parent)
            {
                ret.addEdge(top.parent->name, top.self->name, top.weight);
            }
            for (const auto &edge : top.self->Edges)
            {
                if (!edge.v.expired())
                {
                    auto v = edge.v.lock();
                    if (!checkIncluded(v, included))
                    {
                        pq.push(PrimData<T>(v, top.self, edge.weight));
                    }
                }
            }
        }
    };

    // Passing in empty graph returns empty graph
    if (vertexCount <= 0)
    {
        printf("returning early\n%d", vertexCount);
        return ret;
    }

    // Initialize Data
    std::vector<std::shared_ptr<vertex<T>>>
        vertices{g.getVertices()};
    std::vector<PrimData<T>> primData(g.getCurrentVertices());
    for (int i = 0; i < g.getCurrentVertices(); ++i)
    {
        primData.emplace_back(PrimData<T>{});
    }

    std::priority_queue<PrimData<T>, std::vector<PrimData<T>>, std::greater<PrimData<T>>> pq{};
    std::vector<std::string> included{};
    // RESERVE SIZE OF PRIORITY_QUEUE and INCLUDED
    pq.push(PrimData<T>(vertices[0], std::shared_ptr<vertex<T>>{}, 0));

    // Add first vertex to MST
    //primData[0].weight = 0;
    //primData[0].included = true;
    //addVertexToMST(vertices[0], vertices, primData);

    // Initialize return graph vertices
    for (const auto &v : vertices)
    {
        ret.addVertex(v->name);
    }

    while (!pq.empty())
    {
        addFromPriorityQueue(pq, included);
    }
    /*
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
    */

    return ret;
}