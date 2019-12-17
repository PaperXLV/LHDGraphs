#include "graph.hpp"
#include <limits>
#include <iostream>
#include <algorithm>
#include <queue>

// Struct to hold necesary data for each vertex in the graph
template <typename T>
struct PrimData
{
    PrimData(std::shared_ptr<vertex<T>> s, std::weak_ptr<vertex<T>> p, T w) : parent{p},
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

    std::weak_ptr<vertex<T>> parent{};
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

// Utilizes Prim's Algorithm to generate and return the MST of g
template <typename T>
Graph<T> PrimsMST(const Graph<T> &g)
{
    Graph<T> mst{};
    const int vertexCount = g.getCurrentVertices();

    auto checkIncluded = [&](const std::shared_ptr<vertex<T>> &v, const std::vector<std::string> &included) -> bool {
        return std::binary_search(included.begin(), included.end(), v->name);
    };

    auto insertSorted = [&](std::vector<std::string> &vec, std::string &add) -> void {
        vec.insert(std::upper_bound(vec.begin(), vec.end(), add), add);
    };

    const auto vertices = g.getVertices();

    // Passing in empty graph returns empty graph
    if (vertexCount <= 0)
    {
        printf("returning early\n%d", vertexCount);
        return mst;
    }

    // Initialize Data
    std::vector<std::string> included{};
    std::vector<PrimData<T>> container;
    included.reserve(vertexCount);
    container.reserve(vertexCount);
    std::priority_queue<PrimData<T>, std::vector<PrimData<T>>, std::greater<PrimData<T>>>
        pq(std::greater<PrimData<T>>(), std::move(container));

    // Add first vertex to the min heap
    pq.push(PrimData<T>(vertices[0], std::shared_ptr<vertex<T>>{}, 0));

    // Initialize return graph vertices
    for (const auto &v : vertices)
    {
        mst.addVertex(v->name);
    }
    // Sort to enable fast edge adding
    mst.sortVertices();

    while (!pq.empty())
    {
        const PrimData<T> top = pq.top();
        pq.pop();

        if (!checkIncluded(top.self, included))
        {
            insertSorted(included, top.self->name);
            if (!top.parent.expired())
            {
                mst.addEdge(top.parent.lock()->name, top.self->name, top.weight);
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
    }

    return mst;
}