#include "graph.hpp"

template <typename T, size_t Size>
void BFT_traversal(std::shared_ptr<vertex<T>> v)
{
    std::cout << v->name << std::endl;
    v->visited = true;

    std::queue<std::shared_ptr<vertex<T>>> q;
    q.push(v);

    std::shared_ptr<vertex<T>> n;

    while (!q.empty())
    {
        n = q.front();
        q.pop();

        for (int i = 0; i < n->Edges.size(); i++)
        {
            if (!n->Edges[i].v.expired())
            {
                std::shared_ptr<vertex<T>> edgeV = n->Edges[i].v.lock();
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

template <typename T, size_t Size>
void DFT_traversal(std::shared_ptr<vertex<T>> v)
{
    std::cout << v->name << std::endl;
    DFT_recursive(v);
}

template <typename T>
void DFT_recursive(std::shared_ptr<vertex<T>> v)
{
    v->visited = true;
    for (int i = 0; i < v->Edges.size(); i++)
    {
        if (!v->Edges[i].v.expired())
        {
            std::shared_ptr<vertex<T>> edgeV = v->Edges[i].v.lock();
            if (!edgeV->visited)
            {
                std::cout << edgeV->name << std::endl;
                DFT_recursive(edgeV);
            }
        }
    }
}

template <typename T, size_t Size>
void printDFT(Graph<T, Size> &graph)
{
    graph.setAllVerticesUnvisited();
    for (int i = 0; i < graph.getCurrentVertices(); i++)
    {
        if (!graph.getVertices()[i]->visited)
        {
            DFT_traversal<T, Size>(graph.getVertices()[i]);
        }
    }
}

template <typename T, size_t Size>
void printBFT(Graph<T, Size> &graph)
{
    graph.setAllVerticesUnvisited();
    for (int i = 0; i < graph.getCurrentVertices(); i++)
    {
        if (!graph.getVertices()[i]->visited)
        {
            BFT_traversal<T, Size>(graph.getVertices()[i]);
        }
    }
}