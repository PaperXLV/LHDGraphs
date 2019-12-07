#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#include "Graph.hpp"

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addVertex(string cityName)
{
	vertex v1;
	v1.name = cityName;
	vertices.push_back(v1);
}

void Graph::addEdge(string city1, string city2, int distance)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].name == city1)
		{
			for (int j = 0; j < vertices.size(); j++)
			{
				if (vertices[j].name == city2 && j != i)
				{
					Edge e0;
					e0.v = &vertices[j];
					e0.distance = distance;
					vertices[i].Edges.push_back(e0);
				}
			}
		}
	}
}

void Graph::displayEdges()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		cout << vertices[i].name << "-->";
		for (int j = 0; j < vertices[i].Edges.size(); j++)
		{
			if (j < vertices[i].Edges.size() - 1)
			{
				cout << vertices[i].Edges[j].v->name << " (" << vertices[i].Edges[j].distance << " miles)***";
			}
			else
			{
				cout << vertices[i].Edges[j].v->name << " (" << vertices[i].Edges[j].distance << " miles)";
			}
		}
		cout << endl;
	}
}

void Graph::setAllVerticesUnvisited()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].visited = false;
	}
}

void Graph::printDFT()
{
	setAllVerticesUnvisited();
	for (int i = 0; i < vertices.size(); i++)
	{
		if (!vertices[i].visited)
			DFT_traversal(&vertices[i]);
	}
}

void Graph::printBFT()
{
	setAllVerticesUnvisited();
	for (int i = 0; i < vertices.size(); i++)
	{
		if (!vertices[i].visited)
			BFT_traversal(&vertices[i]);
	}
}

vertex *Graph::findVertex(string name)
{
	vertex *found;
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

void DFT_recursive(vertex *v)
{
	v->visited = true;
	for (int i = 0; i < v->Edges.size(); i++)
	{
		if (!v->Edges[i].v->visited)
		{
			cout << v->Edges[i].v->name << endl;
			DFT_recursive(v->Edges[i].v);
		}
	}
}

void Graph::BFT_traversal(vertex *v)
{
	cout << v->name << endl;
	v->visited = true;

	queue<vertex *> q;
	q.push(v);

	vertex *n;

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
				cout << n->Edges[i].v->name << endl;
			}
		}
	}
}

void Graph::DFT_traversal(vertex *v)
{
	cout << v->name << endl;
	DFT_recursive(v);
}
