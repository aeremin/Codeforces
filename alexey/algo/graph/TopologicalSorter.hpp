#pragma once

template <class PerEdgeData, class PerVertexData>
class TopologicalSorter {
  private:
    enum class Status { Unprocessed, Started, Finished };

  public:
    TopologicalSorter(const DirectedGraph<PerEdgeData, PerVertexData>& graph)
        : graph_(graph), statuses_(graph_.num_vertices(), Status::Unprocessed) {
        for (size_t i = 0; i < graph_.num_vertices(); ++i)
            if (statuses_[i] == Status::Unprocessed)
                isDAG_ = isDAG_ && dfs_(i);
        if (isDAG_)
            std::reverse(begin(sorted_), end(sorted_));
        else
            sorted_ = {};
    }

    bool isDAG() const { return isDAG_; }
    const std::vector<size_t>& getSortedOrder() const { return sorted_; }

  private:
    bool dfs_(size_t i) {
        statuses_[i] = Status::Started;
        auto res = true;
        for (auto pNei : graph_.out_nbrs(i)) {
            if (statuses_[pNei.first] == Status::Started)
                return false;

            if (statuses_[pNei.first] == Status::Unprocessed)
                res = res && dfs_(pNei.first);
        }

        statuses_[i] = Status::Finished;
        sorted_.push_back(i);
        return res;
    }

    const DirectedGraph<PerEdgeData, PerVertexData>& graph_;
    std::vector<Status> statuses_;
    std::vector<size_t> sorted_;
    bool isDAG_ = true;
};

template <class PerEdgeData, class PerVertexData>
TopologicalSorter<PerEdgeData, PerVertexData> makeTopologicalSorter(
    const DirectedGraph<PerEdgeData, PerVertexData>& graph) {
    return TopologicalSorter<PerEdgeData, PerVertexData>(graph);
}
