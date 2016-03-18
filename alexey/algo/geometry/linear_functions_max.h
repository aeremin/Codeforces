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
void LinearFunctionsMaximum<T>::add_function( T a, T b ) {
    auto insertResult = left_.insert( { { a, b }, std::numeric_limits<T>::lowest() } );
    if ( !insertResult.second )
        return;

    auto insertedIt = insertResult.first;
    while ( insertedIt != begin( left_ ) ) {
        auto prevIt = std::prev( insertedIt );
        insertedIt->second = internal::overtake_point( prevIt->first, insertedIt->first );
        if ( insertedIt->second <= prevIt->second )
            left_.erase( prevIt );
        else
            break;
    }

    while ( std::next( insertedIt ) != end(left_) ) {
        auto nextIt = std::next( insertedIt );
        auto pt = internal::overtake_point( insertedIt->first, nextIt->first );
        if ( nextIt->second >= pt ) {
            left_.erase( insertedIt );
            return;
        }
        else {
            nextIt->second = pt;
            auto nextNextIt = std::next( insertedIt, 2 );
            if ( nextNextIt != end( left_ ) ) {
                auto ptNext = internal::overtake_point( insertedIt->first, nextNextIt->first );
                if ( ptNext >= nextIt->second ) {
                    left_.erase( nextIt );
                }
                else
                    break;
            }
        }
    }
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


