#pragma once
#include <queue>
#include <vector>

#include "graph/graph.h"
#include "iter/range.h"
#include "util/relax.h"

template <bool Directed, class PerEdgeData, class PerVertexData>
class MaxFlowPushRelabel {
  public:
    explicit MaxFlowPushRelabel(const Graph<Directed, PerEdgeData, PerVertexData>& graph)
        : graph_(graph),
          currentPreflow_(graph.num_vertices(), std::vector<PerEdgeData>(graph.num_vertices())),
          capacity_(graph.num_vertices(), std::vector<PerEdgeData>(graph.num_vertices())),
          excess_(graph.num_vertices()),
          height_(graph.num_vertices()),
          heightCounts_(2 * graph.num_vertices()),
          isQueued_(graph.num_vertices()) {
        for (auto from : range(graph_.num_vertices()))
            for (auto [vertex, payload] : graph_.out_nbrs(from))
                capacity_[from][vertex] += payload;
    }

    struct Flow {
        PerEdgeData totalFlow;
        Graph<Directed, PerEdgeData, EmptyStruct> flow;
    };

    Flow GetMaxFlow(int source, int sink) {
        InitializeQueue(source, sink);
        InitializePreflow(source, sink);
        InitializeHeight(source);

        while (!verticesQueue_.empty()) {
            int v = verticesQueue_.front();
            verticesQueue_.pop();
            isQueued_[v] = false;
            Discharge(v);
        }

        for (auto i : range(graph_.num_vertices()))
            assert(i == source || i == sink || excess_[i] == 0);

        assert(excess_[source] + excess_[sink] == 0);
        Flow res = {excess_[sink], Graph<Directed, PerEdgeData, EmptyStruct>(graph_.num_vertices())};
        for (int u : range(graph_.num_vertices()))
            for (int v : range(graph_.num_vertices()))
                if (currentPreflow_[u][v] > 0)
                    res.flow.add_directed_edge(u, v, currentPreflow_[u][v]);
        return res;
    }

  private:
    void InitializeQueue(int source, int sink) {
        std::fill(begin(isQueued_), end(isQueued_), false);
        isQueued_[source] = isQueued_[sink] = true;
        assert(verticesQueue_.empty());
    }

    void InitializePreflow(int source, int sink) {
        for (auto& row : currentPreflow_)
            std::fill(begin(row), end(row), PerEdgeData(0));
        std::fill(begin(excess_), end(excess_), PerEdgeData(0));

        for (auto [vertex, payload] : graph_.out_nbrs(source))
            push_through_edge(source, vertex, payload);
    }

    void InitializeHeight(int source) {
        std::fill(begin(height_), end(height_), 0);
        heightCounts_[0] = graph_.num_vertices();
        set_height(source, graph_.num_vertices());
    }

    void Discharge(int v) {
        for (int u : range(graph_.num_vertices())) {
            try_push(v, u);
            if (excess_[v] <= 0)
                break;
        }
        if (excess_[v] > 0) {
            if (heightCounts_[height_[v]] == 1) {
                GapOptimization(height_[v]);
            } else {
                Relabel(v);
            }
        }
    }

    void try_push(int from, int to) {
        auto amount = std::min(excess_[from], residual_capacity(from, to));
        if (height_[from] == height_[to] + 1 && amount > 0)
            push_through_edge(from, to, amount);
    }

    PerEdgeData residual_capacity(int from, int to) const { return capacity_[from][to] - currentPreflow_[from][to]; }

    void push_through_edge(int from, int to, const PerEdgeData& amount) {
        currentPreflow_[from][to] += amount;
        currentPreflow_[to][from] -= amount;
        assert(residual_capacity(from, to) >= 0);
        excess_[from] -= amount;
        excess_[to] += amount;
        enqueue(to);
    }

    void enqueue(int v) {
        if (!isQueued_[v] && excess_[v] > 0) {
            isQueued_[v] = true;
            verticesQueue_.push(v);
        }
    }

    void Relabel(int v) {
        auto h = std::numeric_limits<int>::max();
        for (int u : range(graph_.num_vertices()))
            if (residual_capacity(v, u) > 0)
                relax_min(h, height_[u] + 1);
        set_height(v, h);
        enqueue(v);
    }

    void GapOptimization(int h) {
        for (int u : range(graph_.num_vertices())) {
            if (height_[u] >= h && height_[u] <= graph_.num_vertices()) {
                set_height(u, graph_.num_vertices() + 1);
                enqueue(u);
            }
        }
    }

    void set_height(int v, int h) {
        assert(h < 2 * graph_.num_vertices());
        heightCounts_[height_[v]]--;
        heightCounts_[h]++;
        height_[v] = h;
    }

  private:
    const Graph<Directed, PerEdgeData, PerVertexData>& graph_;

    std::vector<std::vector<PerEdgeData>> currentPreflow_;
    std::vector<std::vector<PerEdgeData>> capacity_;
    std::vector<PerEdgeData> excess_;
    std::vector<int> height_;
    std::vector<int> heightCounts_;

    std::vector<char> isQueued_;
    std::queue<int> verticesQueue_;
};
