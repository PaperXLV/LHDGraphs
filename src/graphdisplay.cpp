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

constexpr int Size{6};
constexpr int MaxEdges{3};

Graph<int,Size, MaxEdges> dfs(){
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

    return g;
}

void makeGraph(){
    Graph g = dfs();
    const char* names[Size];
    const std::array<vertex<int, MaxEdges>, Size> verticies = g.getVertices();    
    int maxEdges = 0;
    for (int i = 0; i < Size; i++){
        names[i] = verticies[i].name.c_str();
        maxEdges += verticies[i].currentEdges;
    }

    typedef std::pair<int,int> vertexEdge;
    vertexEdge used_by[maxEdges];
    int VELocation = 0;
    for(int i = 0; i < Size; i++){
        for(int j = 0; j < verticies[i].currentEdges; j++){
            Edge newEdge = verticies[i].Edges[j];
            int edgeNumber = -1;
            for(int t = 0; t < Size; t++){
                if(names[t]==newEdge.v->name){
                    edgeNumber = t;
                    t = Size;
                }
                
            } 
            used_by[VELocation] = vertexEdge(i, edgeNumber);
            VELocation++;
        }
        //newEdgeName = verticies[i].Edges;
        int connectingVertex = -1;
        
        //used_by[i] = Edge(i, connectingVertex);
    }
    //Edge used_by[] = {
    //    Edge(Boulder,Denver),
    //};
    const int nedges = sizeof(used_by)/sizeof(vertexEdge);
    int weights[nedges];
    std::fill(weights, weights + nedges, 1);

    //using namespace boost;

    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, 
        boost::property< boost::vertex_color_t, boost::default_color_type >,
        boost::property< boost::edge_weight_t, int >
        > BoostGraph;
    BoostGraph gr(used_by, used_by + nedges, weights, Size);

    ofstream myfile;
    myfile.open ("graph.gv");
    boost::write_graphviz(myfile, gr, boost::make_label_writer(names));
    myfile.close();
    system("xdot graph.gv");
}

int main(int,char*[])
{
  makeGraph();
  return 0;
  
}
