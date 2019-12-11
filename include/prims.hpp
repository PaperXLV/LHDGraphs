#include "graph.hpp"
#include <limits>

template <typename T, size_t Size, size_t MaxEdges>
constexpr Graph<T, Size, MaxEdges> PrimsMST(const Graph<T, Size, MaxEdges> &g)
{
    if (g.getCurrentVertices() <= 0)
    {
        // Probably need some other default return;
        return Graph<T, Size, MaxEdges>{};
    }
    std::array<vertex<T, MaxEdges>, Size>
        includedVertices{g.getVertices()[0]};

    std::array<T, Size> cutEdge{};
    for (T &weight : cutEdge)
    {
        weight = std::numeric_limits<T>::max();
    }
    cutEdge[0] = 0;

    return Graph<T, Size, MaxEdges>{};
}