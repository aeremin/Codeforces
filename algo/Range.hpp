#pragma once
#include <algorithm>

template<typename T>
class Range
{
public:
    Range(T start, T end) : start_(std::min(start, end)), end_(end) {}
    
    
    class Iterator
    {
    public:
        Iterator(T pos) : pos_(pos) {}
        Iterator& operator++( ) { ++pos_; return *this; }
        const T& operator*( ) const {return pos_; }
        bool operator==( const Iterator& other ) const {return pos_ == other.pos_; }
        bool operator!=( const Iterator& other ) const {return !(*this==other); }

    private:
        T pos_;
    };
    
    Iterator begin() const { return {start_}; }
    Iterator end() const { return {end_}; }

    const T start_, end_;
};

template<typename T> Range<T> range(T start, T end) { return{start, end}; }
template<typename T> Range<T> range(T end) { return{0, end}; }