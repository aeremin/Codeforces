#pragma once
#include "graph/graph.h"

namespace GraphHelper
{
    UndirectedGraph<> createLinearGraph(int nVertices);

    UndirectedGraph<> createSimpleCycleGraph( int nVertices );
};

