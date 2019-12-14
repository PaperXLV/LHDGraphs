#include "graph.hpp"

// MOVING DIJKSTRAS. BROKEN PARENT

template <typename T, size_t MaxEdges>
struct DijkData
{
    DijkData() = default;
    DijkData(const DijkData &) = default;
    DijkData(DijkData &&) = default;
    DijkData &operator=(const DijkData &) = default;
    DijkData &operator=(DijkData &&) = default;
    ~DijkData() = default;

    T distance{0};
    std::shared_ptr<vertex<T, MaxEdges>> self{};
    std::shared_ptr<DijkData<T, MaxEdges>> parent{}; //stores edges to adjacent vertices
    bool solved{false};
};

/*
    Dijkstrs's algorithm
        - start is starting city name (string)
        - returns pointer to ending vertex
          with appropriate distance set
*/
template <typename T, size_t Size, size_t MaxEdges>
std::array<std::shared_ptr<DijkData<T, MaxEdges>>, Size> dijkstraSearch(const Graph<T, Size, MaxEdges> &g, std::string start)
{
    using namespace std;
    DijkData<T, MaxEdges> dStart{};
    shared_ptr<vertex<T, MaxEdges>> vStart = g.findVertex(start).lock();
    array<shared_ptr<DijkData<T, MaxEdges>>, Size> solvedList{};

    if (!vStart)
    {
        cout << "Start city not found" << endl;
        return solvedList;
    }
    dStart.self = move(vStart);

    dStart.solved = true;

    // Create a list to store solved vertices
    // and append vStart
    for (auto &ptr : solvedList)
    {
        ptr = make_shared<DijkData<T, MaxEdges>>(DijkData<T, MaxEdges>{});
    }

    int currentIndex = 0;
    solvedList[currentIndex++] = make_shared<DijkData<T, MaxEdges>>(dStart);

    auto checkSolved = [&](const shared_ptr<vertex<T, MaxEdges>> &v) -> bool {
        for (int i = 0; i < currentIndex; ++i)
        {
            if (v == solvedList[i]->self && solvedList[i]->solved)
            {
                return true;
            }
        }
        return false;
    };

    cout << "initialized\n";

    for (int x = 1; x < Size; x++)
    {
        int minDist = INT8_MAX;
        // data to keep track of solved node
        shared_ptr<DijkData<T, MaxEdges>> solvedD = solvedList[currentIndex];

        // iterater across list of solved vertices
        for (int i = 0; i < currentIndex; i++)
        {
            shared_ptr<DijkData<T, MaxEdges>> data = solvedList[i];
            // now iterate s's adjacency list

            for (int j = 0; j < data->self->currentEdges; j++)
            {
                if (!data->self->Edges[j].v.expired())
                {
                    shared_ptr<vertex<T, MaxEdges>> v = data->self->Edges[j].v.lock();
                    if (!checkSolved(v))
                    {
                        //calculate the weight from vSTart
                        int dist = data->distance + data->self->Edges[j].weight;
                        // check if the weight is less than smallest weight thusfar
                        if (dist < minDist)
                        {
                            solvedD->self = v;
                            minDist = dist;
                            //if you had parent ptr, update it here
                            solvedD->parent = solvedList[i];
                        }
                    }
                }
            }
        }

        solvedD->distance = minDist;
        solvedD->solved = true;
        solvedList[currentIndex++] = solvedD;

        for (int i = 0; i < currentIndex; i++)
        {
            cout << solvedList[i]->self->name << ":" << solvedList[i]->distance << ":" << solvedList[i]->parent->self->name << "\n";
        }
        cout << currentIndex << "\n";
    }
    return solvedList;
}

/*
    Print Dijkstrs's path 
        - start is starting city name (string)
        - prints min distance path
*/
template <typename T, size_t Size, size_t MaxEdges>
void dijkstraDisplay(const Graph<T, Size, MaxEdges> &g, std::string start)
{
    using namespace std;
    array<shared_ptr<DijkData<T, MaxEdges>>, Size> dijk = dijkstraSearch(g, start);
    for (int i = 0; i < Size; ++i)
    {
        cout << dijk[i]->self->name << ":" << dijk[i]->distance << "\n";
    }
}