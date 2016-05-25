#pragma once

template<class PerEdgeData>
struct DijkstraResult
{
    vector<PerEdgeData> minimalDistances;
    vector<int> predecessors;
};


template<class PerEdgeData, class PerVertexData>
DijkstraResult<PerEdgeData> getMinimalPathsFrom(const Graph<PerEdgeData, PerVertexData>& graph, int startVertex, PerEdgeData inAccessibleValue)
{
    DijkstraResult<PerEdgeData> result = { vector<PerEdgeData>(graph.num_vertices(), inAccessibleValue), vector<int>(graph.num_vertices(), -1) };
    using FullEdgeData = tuple<PerEdgeData, int, int>;
    priority_queue<FullEdgeData, vector<FullEdgeData>, greater<FullEdgeData>> nextVerticesData;
    nextVerticesData.push(make_tuple(PerEdgeData(), startVertex, startVertex));
    while (!nextVerticesData.empty())
    {
        auto nextVertexData = nextVerticesData.top();
        nextVerticesData.pop();
        auto nextVertexInd = get<1>(nextVertexData);
        if (result.predecessors[nextVertexInd] != -1)
            continue;

        auto nextVertexDist = get<0>(nextVertexData);
        result.minimalDistances[nextVertexInd] = nextVertexDist;
        result.predecessors[nextVertexInd] = get<2>(nextVertexData);
        
        for (auto& p : graph.out_nbrs(nextVertexInd))
            nextVerticesData.push(make_tuple(nextVertexDist + p.second, p.first, nextVertexInd));
    }

    return result;
}

template<class GraphType>
DijkstraResult<int> getMinimalPathsFromUnweighted(const GraphType& graph, int startVertex, int inAccessibleValue) {
    DijkstraResult<int> result = { vector<int>(graph.num_vertices(), inAccessibleValue), vector<int>(graph.num_vertices(), -1) };
    queue<int> verticesQueue;
    verticesQueue.push( startVertex );
    result.minimalDistances[startVertex] = 0;
    result.predecessors[startVertex] = startVertex;
    while (!verticesQueue.empty()) {
        auto v = verticesQueue.front();
        verticesQueue.pop();
        for (auto edge : graph.out_nbrs(v)) {
            auto nei = edge.vertex();
            if (result.predecessors[nei] != -1) continue;
            result.predecessors[nei] = v;
            result.minimalDistances[nei] = result.minimalDistances[v] + 1;
            verticesQueue.push(nei);
        }
    }
    return result;
}
