#include "graph.hpp"

/*
    Dijkstrs's algorithm
        - start is starting city name (string)
        - end is ending city name (string)
        - returns pointer to ending vertex
          with appropriate distance set
*/
template <typename T, size_t Size, size_t MaxEdges>
vertex<T, MaxEdges> *Graph<T, Size, MaxEdges>::dijkstraSearch(std::string start, std::string end)
{
    using namespace std;
    setAllVerticesUnvisited();
    vertex<T, MaxEdges> *vStart = findVertex(start);
    if (!vStart)
    {
        cout << "Start city not found" << endl;
        return nullptr;
    }
    vertex<T, MaxEdges> *vEnd = findVertex(end);
    if (!vEnd)
    {
        cout << "Destination city not found" << endl;
        return nullptr;
    }
    vStart->solved = true;

    // Create a list to store solved vertices
    // and append vStart
    vector<vertex<T, MaxEdges> *> solvedList;
    solvedList.push_back(vStart);

    while (!vEnd->solved)
    {
        int minDist = INT8_MAX;
        // pointer to keep track of solved node
        vertex<T, MaxEdges> *solvedV = nullptr;

        // iterater across list of solved vertices
        for (int i = 0; i < solvedList.size(); i++)
        {
            vertex<T, MaxEdges> *s = solvedList[i];
            // now iterate s's adjacency list

            for (int j = 0; j < s->Edges.size(); j++)
            {
                if (s->Edges[j].v != nullptr)
                {
                    if (!s->Edges[j].v->solved)
                    {
                        //calculate the distance from vSTart
                        int dist = s->distDijk + s->Edges[j].distance;
                        // check if the distance is less than smallest distance thusfar
                        if (dist < minDist)
                        {
                            solvedV = s->Edges[j].v;
                            minDist = dist;
                            //if you had parent ptr, update it here
                            solvedV->dijkParent = s;
                        }
                    }
                }
            }
        }

        solvedV->distDijk = minDist;
        // solvedV->parent
        solvedV->solved = true;
        solvedList.push_back(solvedV);
        // cout << solvedV->name << endl;
    }
    return vEnd;
}

/*
    Print Dijkstrs's path 
        - start is starting city name (string)
        - end is ending city name (string)
        - prints min distance path
*/
template <typename T, size_t Size, size_t MaxEdges>
void Graph<T, Size, MaxEdges>::dijkstraDisplay(std::string start, std::string end)
{
    using namespace std;
    vertex<T, MaxEdges> *vEnd = dijkstraSearch(start, end);
    vertex<T, MaxEdges> *temp = vEnd;
    while (temp != nullptr)
    {
        cout << temp->name << endl;
        temp = temp->dijkParent;
    }
}