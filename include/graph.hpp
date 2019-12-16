#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <array>
#include <queue>
#include <string_view>
#include <memory>
#include <algorithm>

template <typename T>
struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */
template <typename T>
struct Edge
{
    Edge() = default;
    Edge(const Edge &) = default;
    Edge(Edge &&) = default;
    Edge &operator=(const Edge &) = default;
    Edge &operator=(Edge &&) = default;
    ~Edge() = default;

    std::weak_ptr<vertex<T>> v{};
    T weight{0};
};

/*this is the struct for each vertex in the graph. */
template <typename T>
struct vertex
{
    vertex() = default;
    vertex(const vertex &) = default;
    vertex(vertex &&) = default;
    vertex &operator=(const vertex &) = default;
    vertex &operator=(vertex &&) = default;
    ~vertex() = default;

    std::string name{""};
    bool visited{false};
    std::vector<Edge<T>> Edges{}; //stores edges to adjacent vertices
};

/* 
    Main Graph instance
*/
template <typename T>
class Graph
{
public:
    Graph() = default;
    Graph(const Graph &) = default;
    Graph(Graph &&) = default;
    Graph &operator=(const Graph &) = default;
    Graph &operator=(Graph &&) = default;
    ~Graph() = default;

    void addVertex(std::string name);
    void addEdge(std::string_view name1, std::string_view name2, T weight);
    bool inEdges(std::string_view source, std::string_view target) const;

    void displayEdges();
    const std::vector<std::shared_ptr<vertex<T>>> &getVertices() const;
    const std::weak_ptr<vertex<T>> findVertex(std::string_view name) const;
    int getCurrentVertices() const;
    void setAllVerticesUnvisited();
    void sortVertices();
    //void adjListToMat(bool matrix[Size][Size]);
    //void adjListToMat();

private:
    std::vector<std::shared_ptr<vertex<T>>> vertices{}; //stores vertices
    bool vertSorted{false};

    //std::array<std::array<bool>> adjMatrix{};
};

/*
    Add a vertex to the graph
        - Takes in the name (string) of the city to be added
*/
template <typename T>
void Graph<T>::addVertex(std::string cityName)
{
    vertex<T> v1;
    v1.name = cityName;
    vertices.emplace_back(std::make_shared<vertex<T>>(v1));
    vertSorted = false;
}

/*
    Add an edge between two verticies
        - city 2 will be added to city1's adjacency list
        - will only add in a single direction
        - weight is the weight of the Edge between the verticies
*/
template <typename T>
void Graph<T>::addEdge(std::string_view city1, std::string_view city2, T weight)
{
    if (vertSorted)
    {
        auto c1 = std::lower_bound(vertices.begin(), vertices.end(), city1);
        auto city1_access = *c1;
        if (c1 != vertices.end() && city1_access->name == city1)
        {
            auto c2 = std::lower_bound(vertices.begin(), vertices.end(), city2);
            auto city2_access = *c2;
            if (c2 != vertices.end() && city2_access->name == city2)
            {
                Edge<T> e0;
                e0.v = city2_access;
                e0.weight = weight;
                city1_access->Edges.emplace_back(std::move(e0));
            }
        }
    }
    else
    {
        for (int i = 0; i < vertices.size(); ++i)
        {
            if (vertices[i]->name == city1)
            {
                for (int j = 0; j < vertices.size(); ++j)
                {
                    if (vertices[j]->name == city2 && j != i)
                    {
                        Edge<T> e0;
                        e0.v = vertices[j];
                        e0.weight = weight;
                        vertices[i]->Edges.emplace_back(std::move(e0));
                        break;
                    }
                }
                break;
            }
        }
    }
}

/*
    Find a vertex in the Graph
        - returns vertex pointer if found
        - returns nullptr if not found
*/
template <typename T>
const std::weak_ptr<vertex<T>> Graph<T>::findVertex(std::string_view name) const
{
    std::shared_ptr<vertex<T>> found{};
    for (int i = 0; i < vertices.size(); ++i)
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
template <typename T>
void Graph<T>::displayEdges()
{
    for (int i = 0; i < vertices.size(); ++i)
    {
        std::cout << vertices[i]->name << "-->";
        for (int j = 0; j < vertices[i]->Edges.size(); ++j)
        {
            if (j < vertices[i]->Edges.size() - 1)
            {
                std::cout << vertices[i]->Edges[j].v->name << " (" << vertices[i]->Edges[j].weight << " miles)***";
            }
            else
            {
                std::cout << vertices[i]->Edges[j].v->name << " (" << vertices[i]->Edges[j].weight << " miles)";
            }
        }
        std::cout << std::endl;
    }
}

/*
    Check if targetCity is in city's adjacency list
        - returns True if yes, False if no
*/
template <typename T>
bool Graph<T>::inEdges(std::string_view city, std::string_view targetCity) const
{
    std::shared_ptr<vertex<T>> v1 = findVertex(city).lock();
    std::shared_ptr<vertex<T>> v2 = findVertex(targetCity).lock();

    for (const auto edge : v1->Edges)
    {
        if (edge.v.lock() == v2)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
const std::vector<std::shared_ptr<vertex<T>>> &Graph<T>::getVertices() const
{
    return vertices;
}

template <typename T>
int Graph<T>::getCurrentVertices() const
{
    return vertices.size();
}

/*
    Walk through vertices and mark them all unvisited
*/
template <typename T>
void Graph<T>::setAllVerticesUnvisited()
{
    for (int i = 0; i < vertices.size(); ++i)
    {
        vertices[i]->visited = false;
    }
}

template <typename T>
void Graph<T>::sortVertices()
{
    if (!vertSorted)
    {
        std::sort(vertices.begin(), vertices.end());
        vertSorted = true;
    }
}
/*
// User gives a destination matrix to store in
template <typename T>
void Graph<T>::adjListToMat(bool matrix[Size][Size])
{
    using namespace std;
    for (int i = 0; i < Size; ++i)
    {
        for (int j = 0; j < Size; ++j)
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
    for (int i = 0; i < Size; ++i)
    {
        for (int j = 0; j < Size; ++j)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

// default to storing matrix in class adjMatrix
template <typename T>
void Graph<T>::adjListToMat()
{
    using namespace std;
    for (int i = 0; i < Size; ++i)
    {
        for (int j = 0; j < Size; ++j)
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
    for (int i = 0; i < Size; ++i)
    {
        for (int j = 0; j < Size; ++j)
        {
            cout << adjMatrix[i][j] << "  ";
        }
        cout << endl;
    }
}
*/
template <typename T>
constexpr bool operator==(const vertex<T> &ob1, const vertex<T> &ob2)
{
    return ob1.name == ob2.name;
}

template <typename T>
constexpr bool operator!=(const vertex<T> &ob1, const vertex<T> &ob2)
{
    return !(ob1.name == ob2.name);
}

template <typename T>
constexpr bool operator>(const vertex<T> &ob1, const vertex<T> &ob2)
{
    return ob1.name > ob2.name;
}

template <typename T>
constexpr bool operator<(const vertex<T> &ob1, const vertex<T> &ob2)
{
    return ob1.name < ob2.name;
}

template <typename T>
constexpr bool operator==(const std::shared_ptr<vertex<T>> &ob1, const std::string_view &ob2)
{
    return ob1->name == ob2;
}

template <typename T>
constexpr bool operator!=(const std::shared_ptr<vertex<T>> &ob1, const std::string_view &ob2)
{
    return !(ob1->name == ob2);
}

template <typename T>
constexpr bool operator>(const std::shared_ptr<vertex<T>> &ob1, const std::string_view &ob2)
{
    return ob1->name > ob2;
}

template <typename T>
constexpr bool operator<(const std::shared_ptr<vertex<T>> &ob1, const std::string_view &ob2)
{
    return ob1->name < ob2;
}

#endif // GRAPH_HPP
