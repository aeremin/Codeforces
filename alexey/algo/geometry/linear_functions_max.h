#pragma once
#include <set>
#include <limits>
#include <cassert>

template<typename T>
class LinearFunctionsMaximum {
public:
    // adds function y = ax + b.
    void add_function( T a, T b );

    // returns max(a_i * x + b_i)
    T get_value( T x ) const;

    bool is_empty() const { return left_.empty(); }

private:
    bool try_to_eliminate(typename std::map<std::pair<T, T>, T>::iterator it);

    std::map<std::pair<T, T>, T> left_;
};

namespace internal
{
template<typename T>
T overtake_point( const std::pair<T, T>& fn1, const std::pair<T, T>& fn2 ) {
    assert( fn2.first >= fn1.first );
    if ( fn2.first == fn1.first ) {
        assert( fn2.second > fn1.second );
        return std::numeric_limits<T>::lowest();
    }
    auto res = ( fn1.second - fn2.second ) / ( fn2.first - fn1.first );
    if ( fn2.first * res + fn2.second < fn1.first * res + fn1.second )
        res += T( 1 );
    assert( fn2.first * res + fn2.second >= fn1.first * res + fn1.second );
    return res;
}
}

template<typename T>
bool LinearFunctionsMaximum<T>::try_to_eliminate(typename std::map<std::pair<T, T>, T>::iterator it) {
    if (it != begin(left_) && it != std::prev(end(left_))) {
        auto nextIt = std::next(it);
        if (nextIt->second <= it->second) {
            left_.erase(it);
            auto prevIt = std::prev(nextIt);
            nextIt->second = internal::overtake_point(prevIt->first, nextIt->first);
            return true;
        }
    }
    return false;
}

template<typename T>
void LinearFunctionsMaximum<T>::add_function( T a, T b ) {
    auto insertResult = left_.insert( { { a, b }, std::numeric_limits<T>::lowest() } );
    if ( !insertResult.second )
        return;

    auto insertedIt = insertResult.first;
    if (insertedIt != begin(left_))
        insertedIt->second = internal::overtake_point(std::prev(insertedIt)->first, insertedIt->first);

    auto nextIt = std::next(insertedIt);
    if (nextIt != end(left_))
        nextIt->second = internal::overtake_point(insertedIt->first, nextIt->first);

    if (try_to_eliminate(insertedIt))
        return;

    while (insertedIt != begin(left_) && try_to_eliminate(std::prev(insertedIt))) {}
    while (insertedIt != std::prev(end(left_)) && try_to_eliminate(std::next(insertedIt))) {}
}


template<typename T>
T LinearFunctionsMaximum<T>::get_value( T x ) const {
    auto eltToFind = std::make_pair( std::make_pair( T(), T() ), x );
    auto cmp = []( const std::pair<std::pair<T, T>, T>& lh, const std::pair<std::pair<T, T>, T>& rh ) {return lh.second < rh.second; };
    auto it = std::upper_bound( begin( left_ ), end( left_ ), eltToFind, cmp );
    --it;
    auto& func = it->first;
    return func.first * x + func.second;
}


