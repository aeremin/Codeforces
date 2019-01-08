#pragma once
#include "algo/graph/Graph.hpp"

namespace GraphHelper
{
    UndirectedGraph<> createLinearGraph(int nVertices);

    UndirectedGraph<> createSimpleCycleGraph( int nVertices );
};

