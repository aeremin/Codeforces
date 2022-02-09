#pragma once

namespace update_types {

struct Id {
  public:
    friend Id operator*(const Id& lh, const Id& rh) { return {}; }
};

}  // namespace update_types
