#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <array>
#include <queue>

template <typename T>
struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

template <typename T>
struct Edge
{
    vertex<T> *v;
    T distance;
};

/*this is the struct for each vertex in the graph. */
template <typename T>
struct vertex
{
    std::string name;
    bool visited;
    std::vector<Edge<T>> Edges; //stores edges to adjacent vertices
};

template <typename T, size_t Size>
class Graph
{
public:
    constexpr Graph() {}

    void addVertex(std::string cityName);
    void addEdge(std::string city1, std::string city2, T distance);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();

private:
    std::array<vertex<T>, Size> vertices; //stores vertices

    vertex<T> *findVertex(std::string name);

    void BFT_traversal(vertex<T> *v);
    void DFT_traversal(vertex<T> *v);
};

template <typename T, size_t Size>
void Graph<T, Size>::addVertex(std::string cityName)
{
    static int current = 0;
    vertex<T> v1;
    v1.name = cityName;
    vertices[current] = v1;
    current += 1;
}

template <typename T, size_t Size>
void Graph<T, Size>::addEdge(std::string city1, std::string city2, T distance)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == city1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j].name == city2 && j != i)
                {
                    Edge<T> e0;
                    e0.v = &vertices[j];
                    e0.distance = distance;
                    vertices[i].Edges.push_back(e0);
                }
            }
        }
    }
}

template <typename T, size_t Size>
void Graph<T, Size>::displayEdges()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i].name << "-->";
        for (int j = 0; j < vertices[i].Edges.size(); j++)
        {
            if (j < vertices[i].Edges.size() - 1)
            {
                std::cout << vertices[i].Edges[j].v->name << " (" << vertices[i].Edges[j].distance << " miles)***";
            }
            else
            {
                std::cout << vertices[i].Edges[j].v->name << " (" << vertices[i].Edges[j].distance << " miles)";
            }
        }
        std::cout << std::endl;
    }
}

template <typename T, size_t Size>
void Graph<T, Size>::setAllVerticesUnvisited()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
}

template <typename T, size_t Size>
void Graph<T, Size>::printDFT()
{
    setAllVerticesUnvisited();
    for (int i = 0; i < vertices.size(); i++)
    {
        if (!vertices[i].visited)
            DFT_traversal(&vertices[i]);
    }
}

template <typename T, size_t Size>
void Graph<T, Size>::printBFT()
{
    setAllVerticesUnvisited();
    for (int i = 0; i < vertices.size(); i++)
    {
        if (!vertices[i].visited)
            BFT_traversal(&vertices[i]);
    }
}

template <typename T, size_t Size>
vertex<T> *Graph<T, Size>::findVertex(std::string name)
{
    vertex<T> *found;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == name)
        {
            found = &vertices[i];
            break;
        }
    }

    return found;
}

template <typename T>
void DFT_recursive(vertex<T> *v)
{
    v->visited = true;
    for (int i = 0; i < v->Edges.size(); i++)
    {
        if (!v->Edges[i].v->visited)
        {
            std::cout << v->Edges[i].v->name << std::endl;
            DFT_recursive(v->Edges[i].v);
        }
    }
}

template <typename T, size_t Size>
void Graph<T, Size>::BFT_traversal(vertex<T> *v)
{
    std::cout << v->name << std::endl;
    v->visited = true;

    std::queue<vertex<T> *> q;
    q.push(v);

    vertex<T> *n;

    while (!q.empty())
    {
        n = q.front();
        q.pop();

        for (int i = 0; i < n->Edges.size(); i++)
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

template <typename T, size_t Size>
void Graph<T, Size>::DFT_traversal(vertex<T> *v)
{
    std::cout << v->name << std::endl;
    DFT_recursive(v);
}

#endif // GRAPH_HPP
