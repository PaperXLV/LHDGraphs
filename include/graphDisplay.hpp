#ifndef GRAPHDISPLAY_HPP
#define GRAPHDISPLAY_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <boost/graph/graphviz.hpp>
#include <graphviz/gvc.h>
#include "graph.hpp"
#include <vector>

//enum files_e{ new1, new2, N };
//const char* name[] = {  "new1", "new2" };

//max number of vectors
//constexpr int Size{6};
//max number of edges per vector
//constexpr int MaxEdges{3};

//makeGraph makes a dot file from a graph object and opens it.
//Takes a graph object as an argument.
template <typename T, size_t Size, size_t MaxEdges>
void makeGraph(Graph<T, Size, MaxEdges> g)
{
    //array of vector names
    const char *names[Size];
    const std::array<vertex<int, MaxEdges>, Size> verticies = g.getVertices();
    // maxEdges is the total edges from all vectors
    int maxEdges = 0;
    // get vector names and number of total edges
    for (int i = 0; i < Size; i++)
    {
        names[i] = verticies[i].name.c_str();
        maxEdges += verticies[i].currentEdges;
    }
    typedef std::pair<int, int> vertexEdge;
    // array of edges to be made in dot file
    vertexEdge usedBy[maxEdges];
    //location in the used_by array while adding values
    int usedByLocation = 0;
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < verticies[i].currentEdges; j++)
        {
            //get the edge arrays for vector
            Edge newEdge = verticies[i].Edges[j];
            int edgeNumber = -1;
            for (int t = 0; t < Size; t++)
            {
                if (names[t] == newEdge.v->name)
                { //find vertex number for name
                    edgeNumber = t;
                    t = Size;
                }
            }
            //add edge to edge dot array
            usedBy[usedByLocation] = vertexEdge(i, edgeNumber);
            usedByLocation++;
        }
        int connectingVertex = -1;
    }

    const int nedges = sizeof(usedBy) / sizeof(vertexEdge);
    int weights[nedges];
    std::fill(weights, weights + nedges, 1);
    //define type of
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                  boost::property<boost::vertex_color_t, boost::default_color_type>,
                                  boost::property<boost::edge_weight_t, int>>
        BoostGraph;
    //make BoostGraph object
    BoostGraph gr(usedBy, usedBy + nedges, weights, Size);

    std::ofstream myfile;
    //write graph to gv file
    myfile.open("graph.gv");
    boost::write_graphviz(myfile, gr, boost::make_label_writer(names));
    myfile.close();
    //open graph
    system("xdot graph.gv");
}

#endif // GRAPHDISPLAY_HPP