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
        processTime_.clear();
        processTime_.resize(graph_.vertexCount());
        fill(begin(processTime_), end(processTime_), numeric_limits<int>::max());

        return processVertex_(vertex, 0);
    }

private:

    bool processVertex_(int vertex, int processTime)
    {
        processTime_[vertex] = processTime;

        if (vertexPreprocessCallback_(vertex))
            return true;

        bool stop = false;
        for (auto& neighbor : graph_.vertexNeighbors(vertex))
        {
            int neighborProcessTime = processTime_[neighbor];
            // Edge to the parent
            if (neighborProcessTime + 1 == processTime)
                continue;

            if (neighborProcessTime == numeric_limits<int>::max())
            {
                //Discovered new vertex
                stop = stop || edgeProcessCallback_(vertex, neighbor, true);
                stop = stop || processVertex_(neighbor, ++processTime);
            }
            else // Already processed vertex
                stop = stop || edgeProcessCallback_(vertex, neighbor, false);

        }
                
        stop = stop || vertexPostprocessCallback_(vertex);
        return stop;
    }

private:
    const Graph& graph_;
    EdgeCallback edgeProcessCallback_;
    VertexCallback vertexPreprocessCallback_;
    VertexCallback vertexPostprocessCallback_;

    vector<int> processTime_;
    int currProccessTime_;
};