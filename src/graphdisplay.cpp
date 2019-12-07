// Copyright 2007 Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// A simple example of using write_graphviz to output a BGL adjacency_list
// graph in GraphViz Dot format.

// Author: Doug Gregor

#include <iostream>
#include <fstream>
#include <string>
#include <boost/graph/graphviz.hpp>
#include <graphviz/gvc.h>
#include "graph.hpp"
#include <vector>

using namespace std;

//enum files_e{ new1, new2, N };
//const char* name[] = {  "new1", "new2" };

constexpr int Size{6}; //max number of vectors
constexpr int MaxEdges{3}; //max number of edges per vector


//makeGraph makes a dot file from a graph object and opens it. 
//Takes a graph object as an argument.
void makeGraph(Graph<int,Size, MaxEdges> g){
    const char* names[Size]; //array of vector names
    const std::array<vertex<int, MaxEdges>, Size> verticies = g.getVertices();    
    int maxEdges = 0; //total edges from all vectors
    for (int i = 0; i < Size; i++){ //get verctor names and number of total edges
        names[i] = verticies[i].name.c_str();
        maxEdges += verticies[i].currentEdges;
    }
    typedef std::pair<int,int> vertexEdge; 
    vertexEdge usedBy[maxEdges];// array of edges to be made in dot file
    int usedByLocation = 0; //location in the used_by array while adding values
    for(int i = 0; i < Size; i++){
        for(int j = 0; j < verticies[i].currentEdges; j++){
            Edge newEdge = verticies[i].Edges[j]; //get the edge arrays for vector
            int edgeNumber = -1;
            for(int t = 0; t < Size; t++){
                if(names[t]==newEdge.v->name){ //find vertex number for name
                    edgeNumber = t;
                    t = Size;
                }
                
            } 
            usedBy[usedByLocation] = vertexEdge(i, edgeNumber); //add edge to edge dot array
            usedByLocation++;
        }
        int connectingVertex = -1;
        
    }

    const int nedges = sizeof(usedBy)/sizeof(vertexEdge);
    int weights[nedges];
    std::fill(weights, weights + nedges, 1);

    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, 
        boost::property< boost::vertex_color_t, boost::default_color_type >,
        boost::property< boost::edge_weight_t, int >
        > BoostGraph; //define type of 
    BoostGraph gr(usedBy, usedBy + nedges, weights, Size); //make BoostGraph object

    ofstream myfile;
    myfile.open ("graph.gv"); //write graph to gv file
    boost::write_graphviz(myfile, gr, boost::make_label_writer(names));
    myfile.close();
    system("xdot graph.gv"); //open graph
}

void dfs(){
    Graph<int, Size, MaxEdges> g;

	g.addVertex("Boulder");
	g.addVertex("Denver");
	g.addVertex("Cheyenne");
	g.addVertex("Fruita");
	g.addVertex("Moab");
	g.addVertex("Las Vegas");

	g.addEdge("Boulder", "Denver", 5);
	g.addEdge("Boulder", "Cheyenne", 4);
	g.addEdge("Boulder", "Fruita", 6);
	g.addEdge("Fruita", "Denver", 2);
	g.addEdge("Cheyenne", "Moab", 9);
	g.addEdge("Moab", "Fruita", 6);
	g.addEdge("Las Vegas", "Moab", 4);


    makeGraph(g);
    return;
}

int main(int,char*[])
{
  dfs();
  return 0;
  
}
