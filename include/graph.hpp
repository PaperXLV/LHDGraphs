#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <array>
#include <queue>

struct constexpr_str
{
    const char *str;
    size_t size;

    // can only construct from a char[] literal
    template <size_t N>
    constexpr constexpr_str(const char (&s)[N])
        : str(s),
          size(N - 1) // not count the trailing nul
    {
    }
    constexpr constexpr_str() : str{"\0"}, size(0) {}

    bool operator==(constexpr_str &obj)
    {
        return str == obj.str;
    }
};

std::ostream &operator<<(std::ostream &os, const constexpr_str &str)
{
    os << str.str;
    return os;
}

template <typename T, size_t MaxEdges>
struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

template <typename T, size_t MaxEdges>
struct Edge
{
    constexpr Edge() : v{nullptr},
                       distance{0} {};
    vertex<T, MaxEdges> *v;
    T distance;
};

/*this is the struct for each vertex in the graph. */
template <typename T, size_t MaxEdges>
struct vertex
{
    constexpr vertex() : Edges{},
                         visited{false},
                         name(),
                         currentEdges{0} {};

    std::string_view name;
    bool visited;
    int currentEdges;
    std::array<Edge<T, MaxEdges>, MaxEdges> Edges; //stores edges to adjacent vertices
};

template <typename T, size_t Size, size_t MaxEdges>
class Graph
{
public:
    constexpr Graph();
    ~Graph() = default;

    constexpr void addVertex(std::string_view name);
    constexpr void addEdge(std::string_view name1, std::string_view name2, T distance);
    constexpr bool inEdges(std::string_view source, std::string_view target);
    void displayEdges();
    constexpr std::array<vertex<T, MaxEdges>, Size> &getVertices();
    const int getCurrentVertices();
    constexpr void setAllVerticesUnvisited();
    void adjListToMat(bool matrix[Size][Size]);
    void adjListToMat();

private:
    std::array<vertex<T, MaxEdges>, Size> vertices; //stores vertices
    int currentVertices{0};

    std::array<std::array<bool, Size>, Size> adjMatrix;

    constexpr vertex<T, MaxEdges> *findVertex(std::string_view name);
};

template <typename T, size_t Size, size_t MaxEdges>
constexpr Graph<T, Size, MaxEdges>::Graph() : adjMatrix{}
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
constexpr void Graph<T, Size, MaxEdges>::addVertex(std::string_view cityName)
{
    vertex<T, MaxEdges> v1;
    v1.name = cityName;
    vertices[currentVertices] = v1;
    currentVertices++;
}

template <typename T, size_t Size, size_t MaxEdges>
constexpr void Graph<T, Size, MaxEdges>::addEdge(std::string_view city1, std::string_view city2, T distance)
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
constexpr vertex<T, MaxEdges> *Graph<T, Size, MaxEdges>::findVertex(std::string_view name)
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
constexpr bool Graph<T, Size, MaxEdges>::inEdges(std::string_view city, std::string_view targetCity)
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
constexpr std::array<vertex<T, MaxEdges>, Size> &Graph<T, Size, MaxEdges>::getVertices()
{
    return vertices;
}

template <typename T, size_t Size, size_t MaxEdges>
const int Graph<T, Size, MaxEdges>::getCurrentVertices()
{
    return currentVertices;
}

template <typename T, size_t Size, size_t MaxEdges>
constexpr void Graph<T, Size, MaxEdges>::setAllVerticesUnvisited()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
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
