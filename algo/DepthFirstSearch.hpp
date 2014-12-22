#pragma once
#include <vector>
#include <utility>
#include <functional>
#include <limits>
#include "Graph.hpp"

using std::vector;
using std::pair;
using std::make_pair;
using std::function;
using std::fill;
using std::numeric_limits;


class DepthFirstSearcher
{
public:
    typedef function<bool(int, int, bool)> EdgeCallback;
    typedef function<bool(int)> VertexCallback;

public:
    DepthFirstSearcher(const Graph& graph) : graph_(graph),
        edgeProcessCallback_( [](int, int, bool)->bool {return false; } ),
        vertexPreprocessCallback_( [](int)->bool {return false; } ),
        vertexPostprocessCallback_( [](int)->bool {return false; } )
    {}

    void setVertexPreprocessCallback(VertexCallback callback)
    {
        vertexPreprocessCallback_ = callback;
    }

    void setVertexPostprocessCallback(VertexCallback callback)
    {
        vertexPostprocessCallback_ = callback;
    }

    void setEdgePostprocessCallback(EdgeCallback callback)
    {
        edgeProcessCallback_ = callback;
    }

    bool search(int vertex)
    {
        auto resetTimeArray = [&](vector<int>& arr)
        {
            arr.clear();
            arr.resize(graph_.vertexCount());
            fill(begin(arr), end(arr), numeric_limits<int>::max());
        };
        resetTimeArray(inTime_);
        resetTimeArray(outTime_);

        currProccessTime_ = 0;
        return processVertex_(vertex);
    }

private:

    bool processVertex_(const int vertex)
    {
        inTime_[vertex] = currProccessTime_++;

        if (vertexPreprocessCallback_(vertex))
            return true;

        bool stop = false;
        for (auto& neighbor : graph_.vertexNeighbors(vertex))
        {
            if (inTime_[neighbor] == numeric_limits<int>::max())
            {
                //Discovered new vertex
                stop = stop || edgeProcessCallback_(vertex, neighbor, true);
                stop = stop || processVertex_(neighbor);
            }
            else // Already processed vertex
                if (inTime_[neighbor] < inTime_[vertex]) // To count back-edges only on first encounter
                    stop = stop || edgeProcessCallback_(vertex, neighbor, false);

        }

        outTime_[vertex] = currProccessTime_++;
        stop = stop || vertexPostprocessCallback_(vertex);
        return stop;
    }

private:
    const Graph& graph_;
    EdgeCallback edgeProcessCallback_;
    VertexCallback vertexPreprocessCallback_;
    VertexCallback vertexPostprocessCallback_;

    vector<int> inTime_;
    vector<int> outTime_;
    int currProccessTime_;
};