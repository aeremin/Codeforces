#pragma once
#include "graph/graph.h"
#include "iter/range.h"

inline UndirectedGraph<> ComplementGraph(const UndirectedGraph<>& g) {
    UndirectedGraph<> result(g.num_vertices());
    for (int i : range(g.num_vertices()))
        for (int j : range(i))
            if (!g.has_edge(i, j))
                result.add_edge(i, j);
    return result;
}