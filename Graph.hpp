#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
using namespace std;

struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

struct Edge
{
    vertex *v;
    int distance;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    string name;
    bool visited;
    vector<Edge> Edges; //stores edges to adjacent vertices
};

class Graph
{
public:
    Graph();
    ~Graph();
    void addVertex(string cityName);
    void addEdge(string city1, string city2, int distance);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();
    void adjListToMat(string cityName);

private:
    vector<vertex> vertices; //stores vertices

    vertex *findVertex(string name);
    void BFT_traversal(vertex *v);
    void DFT_traversal(vertex *v);
};

#endif // GRAPH_HPP
