#pragma once

template<class PerEdgeData>
struct DijkstraResult
{
    vector<PerEdgeData> minimalDistances;
    vector<size_t> predecessors;
};


template<class PerEdgeData, class PerVertexData>
DijkstraResult<PerEdgeData> getMinimalPathsFrom(const Graph<PerEdgeData, PerVertexData>& graph, size_t startVertex, PerEdgeData inAccessibleValue)
{
    DijkstraResult<PerEdgeData> result = { vector<PerEdgeData>(graph.vertexCount(), inAccessibleValue), vector<size_t>(graph.vertexCount(), -1) };
    using FullEdgeData = tuple<PerEdgeData, size_t, size_t>;
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
        
        for (auto& p : graph.vertexNeighbors(nextVertexInd))
            nextVerticesData.push(make_tuple(nextVertexDist + p.second, p.first, nextVertexInd));
    }

    return result;
}
