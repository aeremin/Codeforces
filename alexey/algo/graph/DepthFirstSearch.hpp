#pragma once
#include <functional>
#include <limits>
#include <utility>
#include <vector>

#include "graph/graph.h"

using std::fill;
using std::function;
using std::make_pair;
using std::numeric_limits;
using std::pair;
using std::vector;


class DepthFirstSearcher {
  public:
    typedef function<bool(int, int, bool)> EdgeCallback;
    typedef function<bool(int)> VertexCallback;

  public:
    DepthFirstSearcher(const UndirectedGraph<>& graph)
        : graph_(graph),
          edgeProcessCallback_([](int, int, bool) -> bool { return false; }),
          vertexPreprocessCallback_([](int) -> bool { return false; }),
          vertexPostprocessCallback_([](int) -> bool { return false; }) {}

    void setVertexPreprocessCallback(VertexCallback callback) { vertexPreprocessCallback_ = callback; }

    void setVertexPostprocessCallback(VertexCallback callback) { vertexPostprocessCallback_ = callback; }

    void setEdgePostprocessCallback(EdgeCallback callback) { edgeProcessCallback_ = callback; }

    bool search(int vertex) {
        auto resetArray = [&](vector<int>& arr) {
            arr.clear();
            arr.resize(graph_.num_vertices());
            fill(begin(arr), end(arr), numeric_limits<int>::max());
        };
        resetArray(inTime_);
        resetArray(outTime_);
        resetArray(parent_);

        currProccessTime_ = 0;
        parent_[vertex] = -1;
        return processVertex_(vertex);
    }

    int getParent(int vertex) const { return parent_[vertex]; }

    int getInTime(int vertex) const { return inTime_[vertex]; }

    int getOutTime(int vertex) const { return outTime_[vertex]; }

  private:
    bool processVertex_(const int vertex) {
        inTime_[vertex] = currProccessTime_++;

        if (vertexPreprocessCallback_(vertex))
            return true;

        bool stop = false;
        for (auto& edge : graph_.out_nbrs(vertex)) {
            auto neighbor = edge.first;
            if (neighbor == parent_[vertex])
                continue;  // Don't want to process same edge twice

            if (inTime_[neighbor] == numeric_limits<int>::max()) {
                // Discovered new vertex
                parent_[neighbor] = vertex;
                stop = stop || edgeProcessCallback_(vertex, neighbor, true);
                stop = stop || processVertex_(neighbor);
            } else                                        // Already processed vertex
                if (inTime_[neighbor] < inTime_[vertex])  // To count back-edges only on first encounter
                stop = stop || edgeProcessCallback_(vertex, neighbor, false);
        }

        outTime_[vertex] = currProccessTime_++;
        stop = stop || vertexPostprocessCallback_(vertex);
        return stop;
    }

  private:
    const UndirectedGraph<>& graph_;
    EdgeCallback edgeProcessCallback_;
    VertexCallback vertexPreprocessCallback_;
    VertexCallback vertexPostprocessCallback_;

    vector<int> inTime_;
    vector<int> outTime_;
    vector<int> parent_;
    int currProccessTime_;
};


/////////////////////////////////////////
// Depth-first search based algorithms //
/////////////////////////////////////////

// Checks only component containing startVertex
static bool hasCycle(const UndirectedGraph<>& graph, vector<int>* cycle = nullptr, int startVertex = 0) {
    DepthFirstSearcher searcher(graph);

    int backEdgeFrom = 0;
    int backEdgeTo = 0;

    searcher.setEdgePostprocessCallback([&](int from, int to, bool discovery) -> bool {
        if (!discovery) {
            backEdgeFrom = from;
            backEdgeTo = to;
            return true;
        }
        return false;
    });

    bool result = searcher.search(startVertex);

    if (result && cycle) {
        cycle->clear();
        cycle->push_back(backEdgeTo);
        for (int vertex = backEdgeFrom; vertex != backEdgeTo; vertex = searcher.getParent(vertex))
            cycle->push_back(vertex);
    }

    return result;
}