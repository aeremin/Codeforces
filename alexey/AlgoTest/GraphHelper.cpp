#include "GraphHelper.h"

namespace GraphHelper
{
    UndirectedGraph<> createLinearGraph(int nVertices)
    {
        UndirectedGraph<> result( nVertices );
        for (int i = 0; i < nVertices - 1; ++i)
            result.add_edge(i, i + 1);

        return result;
    }

    UndirectedGraph<> createSimpleCycleGraph( int nVertices )
    {
        UndirectedGraph<> result( nVertices );
        for (int i = 0; i < nVertices; ++i)
            result.add_edge(i, (i + 1) % nVertices);

        return result;
    }
}