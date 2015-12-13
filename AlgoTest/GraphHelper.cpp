#include "GraphHelper.h"

namespace GraphHelper
{
    Graph createLinearGraph(int nVertices)
    {
        Graph result(nVertices);
        for (int i = 0; i < nVertices - 1; ++i)
            result.addEdge(i, i + 1);

        return result;
    }

    Graph createSimpleCycleGraph(int nVertices)
    {
        Graph result(nVertices);
        for (int i = 0; i < nVertices; ++i)
            result.addEdge(i, (i + 1) % nVertices);

        return result;
    }
}