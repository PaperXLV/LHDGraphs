#include "graph.hpp"

// MOVING DIJKSTRAS. BROKEN PARENT

template <typename T>
struct DijkData
{
    DijkData() = default;
    DijkData(const DijkData &) = default;
    DijkData(DijkData &&) = default;
    DijkData &operator=(const DijkData &) = default;
    DijkData &operator=(DijkData &&) = default;
    ~DijkData() = default;

    T distance{0};
    std::shared_ptr<vertex<T>> self{};
    std::shared_ptr<DijkData<T>> parent{}; //stores edges to adjacent vertices
    bool solved{false};
};

/*
    Dijkstrs's algorithm
        - start is starting city name (string)
        - returns pointer to ending vertex
          with appropriate distance set
*/
template <typename T>
std::vector<std::shared_ptr<DijkData<T>>> dijkstraSearch(const Graph<T> &g, std::string start)
{
    using namespace std;
    DijkData<T> dStart{};
    shared_ptr<vertex<T>> vStart = g.findVertex(start).lock();
    vector<shared_ptr<DijkData<T>>> solvedList{};

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
        ptr = make_shared<DijkData<T>>(DijkData<T>{});
    }

    solvedList.emplace_back(make_shared<DijkData<T>>(dStart));

    auto checkSolved = [&](const shared_ptr<vertex<T>> &v) -> bool {
        for (int i = 0; i < solvedList.size(); ++i)
        {
            if (v->name == solvedList[i]->self->name && solvedList[i]->solved)
            {
                return true;
            }
        }
        return false;
    };

    for (int x = 1; x < g.getCurrentVertices(); x++)
    {
        int minDist = INT8_MAX;
        // data to keep track of solved node
        shared_ptr<DijkData<T>> solvedD = make_shared<DijkData<T>>(DijkData<T>{});

        // iterater across list of solved vertices
        for (int i = 0; i < solvedList.size(); i++)
        {
            shared_ptr<DijkData<T>> data = solvedList[i];
            // now iterate s's adjacency list

            for (int j = 0; j < data->self->Edges.size(); j++)
            {
                if (!data->self->Edges[j].v.expired())
                {
                    shared_ptr<vertex<T>> v = data->self->Edges[j].v.lock();
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
                            solvedD->parent = data;
                        }
                    }
                }
            }
        }

        if (minDist < INT8_MAX)
        {
            solvedD->distance = minDist;
            solvedD->solved = true;
            solvedList.emplace_back(std::move(solvedD));
        }
    }
    return solvedList;
}

/*
    Print Dijkstrs's path 
        - start is starting city name (string)
        - prints min distance path
*/
template <typename T>
void dijkstraDisplay(const Graph<T> &g, std::string start)
{
    using namespace std;
    vector<shared_ptr<DijkData<T>>> dijk = dijkstraSearch(g, start);
    for (int i = 0; i < dijk.size(); ++i)
    {
        cout << dijk[i]->self->name << ":" << dijk[i]->distance << "\n";
    }
}