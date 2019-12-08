#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <array>
#include <queue>

template <typename T, size_t MaxEdges>
struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

template <typename T, size_t MaxEdges>
struct Edge
{
    vertex<T, MaxEdges> *v;
    T distance;
};

/*this is the struct for each vertex in the graph. */
template <typename T, size_t MaxEdges>
struct vertex
{
    constexpr vertex()
    {
        name = "";
        visited = false;
        currentEdges = 0;
        Edges = {};
    };

    std::string name;
    bool visited;
    int currentEdges;
    std::array<Edge<T, MaxEdges>, MaxEdges> Edges; //stores edges to adjacent vertices
};

template <typename T, size_t Size, size_t MaxEdges>
class Graph
{
public:
    constexpr Graph();

    void addVertex(std::string cityName);
    void addEdge(std::string city1, std::string city2, T distance);
    bool inEdges(std::string city, std::string targetCity);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();
    const std::array<vertex<T, MaxEdges>, Size>& getVertices();
    void adjListToMat(bool matrix[Size][Size]);
    void adjListToMat();

private:
    std::array<vertex<T, MaxEdges>, Size> vertices; //stores vertices
    bool adjMatrix[Size][Size];

    vertex<T, MaxEdges> *findVertex(std::string name);
    void BFT_traversal(vertex<T, MaxEdges> *v);
    void DFT_traversal(vertex<T, MaxEdges> *v);
};

template <typename T, size_t Size, size_t MaxEdges>
constexpr Graph<T, Size, MaxEdges>::Graph()
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            adjMatrix[i][j] = false;
        }
    }
}

template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::addVertex(std::string cityName)
{
    static int current = 0;
    vertex<T, MaxEdges> v1;
    v1.name = cityName;
    vertices[current] = v1;
    current += 1;
}

template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::addEdge(std::string city1, std::string city2, T distance)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == city1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j].name == city2 && j != i)
                {
                    Edge<T, MaxEdges> e0;
                    e0.v = &vertices[j];
                    e0.distance = distance;
                    vertices[i].Edges[vertices[i].currentEdges] = e0;
                    vertices[i].currentEdges++;
                }
            }
        }
    }
}

template <typename T, size_t Size, size_t MaxEdges>
vertex<T, MaxEdges> *Graph<T, Size, MaxEdges>::findVertex(std::string name)
{
    vertex<T, MaxEdges> *found;
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

template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::displayEdges()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i].name << "-->";
        for (int j = 0; j < vertices[i].currentEdges; j++)
        {
            if (j < vertices[i].currentEdges - 1)
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

template <typename T, size_t Size, size_t MaxEdges>
bool Graph<T, Size, MaxEdges>::inEdges(std::string city, std::string targetCity)
{
    vertex<T, MaxEdges> *v1 = findVertex(city);
    vertex<T, MaxEdges> *v2 = findVertex(targetCity);

    for (const auto edge : v1->Edges)
    {
        if (edge.v == v2)
        {
            return true;
        }
    }

    return false;
}

template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::setAllVerticesUnvisited()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
}

template <typename T, size_t Size, size_t MaxEdges>
const std::array<vertex<T, MaxEdges>, Size>& Graph<T, Size, MaxEdges>::getVertices()
{
    return vertices;
}

template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::printDFT()
{
    setAllVerticesUnvisited();
    for (int i = 0; i < vertices.size(); i++)
    {
        if (!vertices[i].visited)
            DFT_traversal(&vertices[i]);
    }
}

template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::printBFT()
{
    setAllVerticesUnvisited();
    for (int i = 0; i < vertices.size(); i++)
    {
        if (!vertices[i].visited)
            BFT_traversal(&vertices[i]);
    }
}

template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::BFT_traversal(vertex<T, MaxEdges> *v)
{
    std::cout << v->name << std::endl;
    v->visited = true;

    std::queue<vertex<T, MaxEdges> *> q;
    q.push(v);

    vertex<T, MaxEdges> *n;

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
void Graph<T, Size, MaxEdges>::DFT_traversal(vertex<T, MaxEdges> *v)
{
    std::cout << v->name << std::endl;
    DFT_recursive(v);
}

template <typename T, size_t MaxEdges>
void DFT_recursive(vertex<T, MaxEdges> *v)
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

// User gives a destination matrix to store in
template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::adjListToMat(bool matrix[Size][Size])
{
    using namespace std;
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            // if (vertices[i].name != "")
            // {
            if (inEdges(vertices[j].name, vertices[i].name))
            {
                matrix[i][j] = true;
                cout << vertices[j].name << "-->" << vertices[i].name << "(" << i << "," << j << ")" << endl;
            }
            // cout << v->name << "-->" << v->Edges[i].v->name << endl;
            if (inEdges(vertices[i].name, vertices[j].name))
            {
                matrix[j][i] = true;
                cout << vertices[i].name << "-->" << vertices[j].name << "(" << j << "," << i << ")" << endl;
            }
            // }
        }
    }
    // Display matrix
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

// default to storing matrix in class adjMatrix
template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::adjListToMat()
{
    using namespace std;
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            // if (vertices[i].name != "")
            // {
            if (inEdges(vertices[j].name, vertices[i].name))
            {
                adjMatrix[i][j] = true;
                cout << vertices[j].name << "-->" << vertices[i].name << "(" << i << "," << j << ")" << endl;
            }
            // cout << v->name << "-->" << v->Edges[i].v->name << endl;
            if (inEdges(vertices[i].name, vertices[j].name))
            {
                adjMatrix[j][i] = true;
                cout << vertices[i].name << "-->" << vertices[j].name << "(" << j << "," << i << ")" << endl;
            }
            // }
        }
    }
    // Display matrix
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            cout << adjMatrix[i][j] << "  ";
        }
        cout << endl;
    }
}

#endif // GRAPH_HPP
