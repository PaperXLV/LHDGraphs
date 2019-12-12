#include "graph.hpp"

template <typename T, size_t Size, size_t MaxEdges>
void BFT_traversal(std::shared_ptr<vertex<T, MaxEdges>> v)
{
    std::cout << v->name << std::endl;
    v->visited = true;

    std::queue<std::shared_ptr<vertex<T, MaxEdges>>> q;
    q.push(v);

    std::shared_ptr<vertex<T, MaxEdges>> n;

    while (!q.empty())
    {
        n = q.front();
        q.pop();

        for (int i = 0; i < n->currentEdges; i++)
        {
            if (!n->Edges[i].v.expired())
            {
                std::shared_ptr<vertex<T, MaxEdges>> edgeV = n->Edges[i].v.lock();
                if (!edgeV->visited)
                {
                    edgeV->visited = true;
                    q.push(edgeV);
                    std::cout << edgeV->name << std::endl;
                }
            }
        }
    }
}

template <typename T, size_t Size, size_t MaxEdges>
void DFT_traversal(std::shared_ptr<vertex<T, MaxEdges>> v)
{
    std::cout << v->name << std::endl;
    DFT_recursive(v);
}

template <typename T, size_t MaxEdges>
void DFT_recursive(std::shared_ptr<vertex<T, MaxEdges>> v)
{
    v->visited = true;
    for (int i = 0; i < v->currentEdges; i++)
    {
        if (!v->Edges[i].v.expired())
        {
            std::shared_ptr<vertex<T, MaxEdges>> edgeV = v->Edges[i].v.lock();
            if (!edgeV->visited)
            {
                std::cout << edgeV->name << std::endl;
                DFT_recursive(edgeV);
            }
        }
    }
}

template <typename T, size_t Size, size_t MaxEdges>
void printDFT(Graph<T, Size, MaxEdges> &graph)
{
    graph.setAllVerticesUnvisited();
    for (int i = 0; i < graph.getCurrentVertices(); i++)
    {
        if (!graph.getVertices()[i]->visited)
        {
            DFT_traversal<T, Size, MaxEdges>(graph.getVertices()[i]);
        }
    }
}

template <typename T, size_t Size, size_t MaxEdges>
void printBFT(Graph<T, Size, MaxEdges> &graph)
{
    graph.setAllVerticesUnvisited();
    for (int i = 0; i < graph.getCurrentVertices(); i++)
    {
        if (!graph.getVertices()[i]->visited)
        {
            BFT_traversal<T, Size, MaxEdges>(graph.getVertices()[i]);
        }
    }
}