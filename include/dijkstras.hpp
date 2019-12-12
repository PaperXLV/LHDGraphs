#include "graph.hpp"

/*
    Dijkstrs's algorithm
        - start is starting city name (string)
        - end is ending city name (string)
        - returns pointer to ending vertex
          with appropriate distance set
*/
template <typename T, size_t Size, size_t MaxEdges>
std::weak_ptr<vertex<T, MaxEdges>> Graph<T, Size, MaxEdges>::dijkstraSearch(std::string start, std::string end)
{
    using namespace std;
    setAllVerticesUnvisited();
    shared_ptr<vertex<T, MaxEdges>> vStart = findVertex(start).lock();
    if (!vStart)
    {
        cout << "Start city not found" << endl;
        return std::weak_ptr<vertex<T, MaxEdges>>{};
    }
    shared_ptr<vertex<T, MaxEdges>> vEnd = findVertex(end).lock();
    if (!vEnd)
    {
        cout << "Destination city not found" << endl;
        return std::weak_ptr<vertex<T, MaxEdges>>{};
    }
    vStart->solved = true;

    // Create a list to store solved vertices
    // and append vStart
    array<shared_ptr<vertex<T, MaxEdges>>, MaxEdges> solvedList;
    int currentIndex = 0;
    solvedList[currentIndex++] = vStart;

    while (!vEnd->solved)
    {
        int minDist = INT8_MAX;
        // pointer to keep track of solved node
        shared_ptr<vertex<T, MaxEdges>> solvedV = nullptr;

        // iterater across list of solved vertices
        for (int i = 0; i < currentIndex; i++)
        {
            shared_ptr<vertex<T, MaxEdges>> s = solvedList[i];
            // now iterate s's adjacency list

            for (int j = 0; j < s->currentEdges; j++)
            {
                if (!s->Edges[j].v.expired())
                {
                    shared_ptr<vertex<T, MaxEdges>> v = s->Edges[j].v.lock();
                    if (!v->solved)
                    {
                        //calculate the distance from vSTart
                        int dist = s->distDijk + s->Edges[j].distance;
                        // check if the distance is less than smallest distance thusfar
                        if (dist < minDist)
                        {
                            solvedV = v;
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
        solvedList[currentIndex++] = solvedV;
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
    shared_ptr<vertex<T, MaxEdges>> vEnd = dijkstraSearch(start, end).lock();
    shared_ptr<vertex<T, MaxEdges>> temp = vEnd;
    while (temp != nullptr)
    {
        cout << temp->name << endl;
        temp = temp->dijkParent.lock();
    }
    cout << "Total Distance: " << vEnd->distDijk << endl;
}