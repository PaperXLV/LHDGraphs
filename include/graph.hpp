#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <array>
#include <queue>
#include <string_view>
#include <memory>

template <typename T, size_t MaxEdges>
struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */
template <typename T, size_t MaxEdges>
struct Edge
{
    Edge() : v{nullptr},
             distance{0} {};
    std::shared_ptr<vertex<T, MaxEdges>> v;
    // distance of the single edge
    T distance;
};

/*this is the struct for each vertex in the graph. */
template <typename T, size_t MaxEdges>
struct vertex
{
    vertex() : Edges{},
               visited{false},
               name{""},
               currentEdges{0},
               solved{false},
               distDijk{0},
               dijkParent{nullptr} {};

    std::string name;
    bool visited;
    int currentEdges;
    std::array<Edge<T, MaxEdges>, MaxEdges> Edges; //stores edges to adjacent vertices

    // distDijk for weighted distance from starting vertex
    T distDijk;
    std::shared_ptr<vertex<T, MaxEdges>> dijkParent; //stores edges to adjacent vertices
    // solved member for Dijkstra's
    bool solved;
};

/* 
    Main Graph instance
*/
template <typename T, size_t Size, size_t MaxEdges>
class Graph
{
public:
    Graph();
    ~Graph() = default;

    void addVertex(std::string name);
    void addEdge(std::string_view name1, std::string_view name2, T distance);
    bool inEdges(std::string_view source, std::string_view target);

    void displayEdges();
    const std::array<std::shared_ptr<vertex<T, MaxEdges>>, Size> &getVertices() const;
    int getCurrentVertices() const;
    void setAllVerticesUnvisited();
    void adjListToMat(bool matrix[Size][Size]);
    void adjListToMat();
    std::shared_ptr<vertex<T, MaxEdges>> dijkstraSearch(std::string start, std::string end);
    void dijkstraDisplay(std::string start, std::string end);

private:
    std::array<std::shared_ptr<vertex<T, MaxEdges>>, Size> vertices; //stores vertices
    int currentVertices{0};

    std::array<std::array<bool, Size>, Size> adjMatrix;

    const std::shared_ptr<vertex<T, MaxEdges>> findVertex(std::string_view name);
};

/*
    Graph constructor. Initializes its adjMatrix to zeros
*/
template <typename T, size_t Size, size_t MaxEdges>
Graph<T, Size, MaxEdges>::Graph() : adjMatrix{}
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            adjMatrix[i][j] = false;
        }
    }
}

/*
    Add a vertex to the graph
        - Takes in the name (string) of the city to be added
*/
template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::addVertex(std::string cityName)
{
    vertex<T, MaxEdges> v1;
    v1.name = cityName;
    vertices[currentVertices] = std::make_shared<vertex<T, MaxEdges>>(v1);
    currentVertices++;
}

/*
    Add an edge between two verticies
        - city 2 will be added to city1's adjacency list
        - will only add in a single direction
        - distance is the weight of the Edge between the verticies
*/
template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::addEdge(std::string_view city1, std::string_view city2, T distance)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == city1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j]->name == city2 && j != i)
                {
                    Edge<T, MaxEdges> e0;
                    e0.v = vertices[j];
                    e0.distance = distance;
                    vertices[i]->Edges[vertices[i]->currentEdges] = e0;
                    vertices[i]->currentEdges++;
                }
            }
        }
    }
}

/*
    Find a vertex in the Graph
        - returns vertex pointer if found
        - returns nullptr if not found
*/
template <typename T, size_t Size, size_t MaxEdges>
const std::shared_ptr<vertex<T, MaxEdges>> Graph<T, Size, MaxEdges>::findVertex(std::string_view name)
{
    std::shared_ptr<vertex<T, MaxEdges>> found = nullptr;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == name)
        {
            found = vertices[i];
            break;
        }
    }

    return found;
}

/*
    Display edges in no particular order
*/
template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::displayEdges()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i]->name << "-->";
        for (int j = 0; j < vertices[i]->currentEdges; j++)
        {
            if (j < vertices[i]->currentEdges - 1)
            {
                std::cout << vertices[i]->Edges[j].v->name << " (" << vertices[i]->Edges[j].distance << " miles)***";
            }
            else
            {
                std::cout << vertices[i]->Edges[j].v->name << " (" << vertices[i]->Edges[j].distance << " miles)";
            }
        }
        std::cout << std::endl;
    }
}

/*
    Check if targetCity is in city's adjacency list
        - returns True if yes, False if no
*/
template <typename T, size_t Size, size_t MaxEdges>
bool Graph<T, Size, MaxEdges>::inEdges(std::string_view city, std::string_view targetCity)
{
    std::shared_ptr<vertex<T, MaxEdges>> v1 = findVertex(city);
    std::shared_ptr<vertex<T, MaxEdges>> v2 = findVertex(targetCity);

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
const std::array<std::shared_ptr<vertex<T, MaxEdges>>, Size> &Graph<T, Size, MaxEdges>::getVertices() const
{
    return vertices;
}

template <typename T, size_t Size, size_t MaxEdges>
int Graph<T, Size, MaxEdges>::getCurrentVertices() const
{
    return currentVertices;
}

/*
    Walk through vertices and mark them all unvisited
*/
template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::setAllVerticesUnvisited()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i]->visited = false;
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
            if (inEdges(vertices[j]->name, vertices[i]->name))
            {
                matrix[i][j] = true;
                cout << vertices[j]->name << "-->" << vertices[i]->name << "(" << i << "," << j << ")" << endl;
            }
            if (inEdges(vertices[i]->name, vertices[j]->name))
            {
                matrix[j][i] = true;
                cout << vertices[i]->name << "-->" << vertices[j]->name << "(" << j << "," << i << ")" << endl;
            }
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
            if (inEdges(vertices[j]->name, vertices[i]->name))
            {
                adjMatrix[i][j] = true;
                cout << vertices[j]->name << "-->" << vertices[i]->name << "(" << i << "," << j << ")" << endl;
            }
            if (inEdges(vertices[i]->name, vertices[j]->name))
            {
                adjMatrix[j][i] = true;
                cout << vertices[i]->name << "-->" << vertices[j]->name << "(" << j << "," << i << ")" << endl;
            }
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

template <typename T, size_t MaxEdges>
constexpr bool operator==(vertex<T, MaxEdges> &ob1, vertex<T, MaxEdges> &ob2)
{
    return ob1.name == ob2.name;
}

template <typename T, size_t MaxEdges>
constexpr bool operator==(const vertex<T, MaxEdges> &ob1, const vertex<T, MaxEdges> &ob2)
{
    return ob1.name == ob2.name;
}

#endif // GRAPH_HPP
