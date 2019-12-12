#include "graph.hpp"

//TODO:: alter algorithm to not take copies and instead const ref
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
            if (!n->Edges[i].v->visited)
            {
                n->Edges[i].v->visited = true;
                q.push(n->Edges[i].v);
                std::cout << n->Edges[i].v->name << std::endl;
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
        if (!v->Edges[i].v->visited)
        {
            std::cout << v->Edges[i].v->name << std::endl;
            DFT_recursive(v->Edges[i].v);
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