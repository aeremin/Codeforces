#pragma once

#if (defined __GNUC__) && !(defined __clang__)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree<T,
                         __gnu_pbds::null_type,
                                     std::less<T>,
                         __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>;

#else
// Very dumb version (complexity is too big to be actually used). 
// Just for compilability check.

#include <set>

template<typename T>
class ordered_set : public std::set<T> {
public:
    typename std::set<T>::iterator find_by_order(size_t ord) { return std::next(this->begin(), ord); }
    size_t order_of_key(const T& key) const { return std::distance(this->begin(), std::lower_bound(this->begin(), this->end(), key)); }
};

#endif