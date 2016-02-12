#pragma once

#pragma once

namespace updateTypes
{

struct Id
{
public:
    friend Id operator*(const Id& lh, const Id& rh) { return{}; }
};

}
