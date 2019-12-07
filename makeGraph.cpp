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
#include <vector>
#include <boost/graph/graphviz.hpp>
#include <graphviz/gvc.h>

using namespace std;



enum files_e{ new1, new2, N };
const char* name[] = {  "new1", "new2" };

void makeGraph(){
    typedef std::pair<int,int> Edge;
    Edge used_by[] = {
    Edge(0,1),
  };
  const int nedges = sizeof(used_by)/sizeof(Edge);
  int weights[nedges];
  std::fill(weights, weights + nedges, 1);

  using namespace boost;

  typedef adjacency_list< vecS, vecS, directedS, 
      property< vertex_color_t, default_color_type >,
      property< edge_weight_t, int >
    > Graph;
  Graph g(used_by, used_by + nedges, weights, N);

  ofstream myfile;
  myfile.open ("graph.gv");
  write_graphviz(myfile, g, make_label_writer(name));
  myfile.close();
  system("xdot graph.gv");
}

int main(int,char*[])
{
  makeGraph();
  return 0;
  
}
