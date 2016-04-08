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

    bool is_empty() const { return funcToOvertake_.empty(); }

private:
    bool try_to_eliminate(typename std::map<std::pair<T, T>, T>::iterator it);

    void set_overtake_point(typename std::map<std::pair<T, T>, T>::iterator it, T val);

    std::set<std::pair<T, std::pair<T, T>>> overtakeToFunc_;
    std::map<std::pair<T, T>, T> funcToOvertake_;
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
void LinearFunctionsMaximum<T>::set_overtake_point(typename std::map<std::pair<T, T>, T>::iterator it, T val) {
    overtakeToFunc_.erase({ it->second, it->first });
    it->second = val;
    overtakeToFunc_.insert({ it->second, it->first });
}

template<typename T>
bool LinearFunctionsMaximum<T>::try_to_eliminate(typename std::map<std::pair<T, T>, T>::iterator it) {
    if (it != std::prev(end(funcToOvertake_))) {
        auto nextIt = std::next(it);
        if (nextIt->second <= it->second) {
            overtakeToFunc_.erase({ it->second, it->first });
            funcToOvertake_.erase(it);
            if (nextIt != begin(funcToOvertake_)) {
                auto prevIt = std::prev(nextIt);
                set_overtake_point(nextIt, internal::overtake_point(prevIt->first, nextIt->first));
            }
            return true;
        }
    }
    return false;
}

template<typename T>
void LinearFunctionsMaximum<T>::add_function( T a, T b ) {
    auto insertResult = funcToOvertake_.insert( { { a, b }, std::numeric_limits<T>::lowest() } );
    if (!insertResult.second)
        return;

    overtakeToFunc_.insert({ std::numeric_limits<T>::lowest(),{ a, b } });

    auto insertedIt = insertResult.first;
    if (insertedIt != begin(funcToOvertake_))
        set_overtake_point(insertedIt, internal::overtake_point(std::prev(insertedIt)->first, insertedIt->first));

    auto nextIt = std::next(insertedIt);
    if (nextIt != end(funcToOvertake_))
        set_overtake_point(nextIt, internal::overtake_point(insertedIt->first, nextIt->first));

    if (try_to_eliminate(insertedIt))
        return;

    while (insertedIt != begin(funcToOvertake_) && try_to_eliminate(std::prev(insertedIt))) {}
    while (insertedIt != std::prev(end(funcToOvertake_)) && try_to_eliminate(std::next(insertedIt))) {}
}


template<typename T>
T LinearFunctionsMaximum<T>::get_value( T x ) const {
    auto it = overtakeToFunc_.upper_bound({ x, { std::numeric_limits<T>::max(), std::numeric_limits<T>::max() } });
    assert(it != begin(overtakeToFunc_));
    --it;
    assert(it != end(overtakeToFunc_));
    auto& func = it->second;
    return func.first * x + func.second;
}


