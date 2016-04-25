#pragma once

#ifdef __GNUC__
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

template<T>
using ordered_set =  tree<T,
                          null_type,
                          less<T>,
                          rb_tree_tag,
                          tree_order_statistics_node_update>;
#else
// Very dumb version (complexity is too big to be actually used). 
// Just for compilability check.

#include <set>

template<typename T>
class ordered_set : public std::set<T> {
public:
    typename std::set<T>::iterator find_by_order(size_t ord) { return std::next(begin(), ord); }
    size_t order_of_key(const T& key) const { return std::distance(begin(), std::lower_bound(begin(), end(), key)); }
};

#endif