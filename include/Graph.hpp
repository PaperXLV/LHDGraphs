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

template <typename T>
class Graph
{
public:
    constexpr Graph() {}

    void addVertex(std::string cityName);
    void addEdge(std::string city1, std::string city2, T distance);
    bool inEdges(std::string city, std::string targetCity);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();
    void adjListToMat(std::string cityName);

private:
    std::vector<vertex<T>> vertices; //stores vertices

    vertex<T> *findVertex(std::string name);

    void BFT_traversal(vertex<T> *v);
    void DFT_traversal(vertex<T> *v);
};

template <typename T>
void Graph<T>::addVertex(std::string cityName)
{
    vertex<T> v1;
    v1.name = cityName;
    vertices.push_back(v1);
}

template <typename T>
void Graph<T>::addEdge(std::string city1, std::string city2, T distance)
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

template <typename T>
void Graph<T>::displayEdges()
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

template <typename T>
void Graph<T>::setAllVerticesUnvisited()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
}

template <typename T>
void Graph<T>::printDFT()
{
    setAllVerticesUnvisited();
    for (int i = 0; i < vertices.size(); i++)
    {
        if (!vertices[i].visited)
            DFT_traversal(&vertices[i]);
    }
}

template <typename T>
void Graph<T>::printBFT()
{
    setAllVerticesUnvisited();
    for (int i = 0; i < vertices.size(); i++)
    {
        if (!vertices[i].visited)
            BFT_traversal(&vertices[i]);
    }
}

template <typename T>
vertex<T> *Graph<T>::findVertex(std::string name)
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

template <typename T>
void Graph<T>::BFT_traversal(vertex<T> *v)
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

template <typename T>
void Graph<T>::DFT_traversal(vertex<T> *v)
{
    std::cout << v->name << std::endl;
    DFT_recursive(v);
}

template <typename T>
bool Graph<T>::inEdges(std::string city, std::string targetCity)
{
    vertex<T> *v1 = findVertex(city);
    vertex<T> *v2 = findVertex(targetCity);

    for (const auto edge : v1->Edges)
    {
        if (edge.v == v2)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
void Graph<T>::adjListToMat(std::string cityName)
{
    using namespace std;
    vertex<T> *v = findVertex(cityName);

    // if edge back to our city exists in the other node's Edges, print the statement
    // for (const auto edge1 : v->Edges)
    // {
    //     cout << v->name << "-->" << edge1.v->name << endl;
    //     for (const auto edge2 : edge1.v->Edges)
    //     {
    //         if (inEdges(edge2.v->name, v->name))
    //         {
    //             cout << v->name << "<--"
    //                  << edge2.v->name << endl;
    //         }
    //     }
    // }

    // for (int i = 0; i < v->Edges.size(); i++)
    // {
    //     for(int j = 0; j < )
    // }
}

#endif // GRAPH_HPP
