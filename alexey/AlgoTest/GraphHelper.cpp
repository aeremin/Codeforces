#include "GraphHelper.h"

namespace GraphHelper
{
    SimpleGraph createLinearGraph(int nVertices)
    {
        SimpleGraph result( nVertices );
        for (int i = 0; i < nVertices - 1; ++i)
            result.add_edge(i, i + 1);

        return result;
    }

    SimpleGraph createSimpleCycleGraph( int nVertices )
    {
        SimpleGraph result( nVertices );
        for (int i = 0; i < nVertices; ++i)
            result.add_edge(i, (i + 1) % nVertices);

        return result;
    }
}