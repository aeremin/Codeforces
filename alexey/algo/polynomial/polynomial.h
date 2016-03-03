#pragma once
#include <vector>
#include "iter/range.h"

template<typename T>
class Polynomial {
public:
    Polynomial() {};
    Polynomial( std::initializer_list<T> coefficients ) : coefficients_( std::move( coefficients ) ) {}
    Polynomial( std::vector<T> coefficients ) : coefficients_( std::move( coefficients ) ) {}

    int formal_degree() const {
        return coefficients_.size() - 1;
    }

    T get_coefficient( int d ) const {
        return ( d > formal_degree() ) ? T( 0 ) : coefficients_[d];
    }

    void set_coefficient( int d, const T& v ) {
        if ( d > formal_degree() )
            coefficients_.resize( d + 1 );
        coefficients_[d] = v;
    }

    T GetValue( const T& pt ) const {
        auto result = T( 0 );
        for ( int i = formal_degree(); i >= 1; --i )
            result = ( result + coefficients_[i] ) * pt;
        
        if ( formal_degree() >= 0 )
            result += coefficients_[0];

        return result;
    }

    bool operator==( const Polynomial<T>& other ) const {
        for ( auto i : range( 1 + std::max( formal_degree(), other.formal_degree() ) ) )
            if ( get_coefficient( i ) != other.get_coefficient( i ) )
                return false;
        return true;
    }

    bool operator!=( const Polynomial<T>& other ) const {
        return !operator==( other );
    }

    const Polynomial<T>& operator+=( const Polynomial<T>& other ) {
        for ( auto i : range( 1 + std::max( formal_degree(), other.formal_degree() ) ) )
            set_coefficient( i, get_coefficient( i ) + other.get_coefficient( i ) );
        return *this;
    }

    const Polynomial<T>& operator-=( const Polynomial<T>& other ) {
        for ( auto i : range( 1 + std::max( formal_degree(), other.formal_degree() ) ) )
            set_coefficient( i, get_coefficient( i ) - other.get_coefficient( i ) );
        return *this;
    }

    const Polynomial<T>& operator*=( const T& v ) {
        for ( auto& c : coefficients_ )
            c *= v;
        return *this;
    }

private:
    std::vector<T> coefficients_;
};

template<typename T>
Polynomial<T> operator+( const Polynomial<T>& lh, const Polynomial<T>& rh ) {
    auto res = lh;
    res += rh;
    return res;
}

template<typename T>
Polynomial<T> operator-( const Polynomial<T>& lh, const Polynomial<T>& rh ) {
    auto res = lh;
    res -= rh;
    return res;
}

template<typename T>
Polynomial<T> operator*( const T& lh, const Polynomial<T>& rh ) {
    auto res = rh;
    res *= lh;
    return res;
}

template<typename T>
Polynomial<T> operator*( const Polynomial<T>& lh, const T& rh ) {
    auto res = lh;
    res *= rh;
    return res;
}

template<typename T>
Polynomial<T> operator*( const Polynomial<T>& lh, const Polynomial<T>& rh ) {
    std::vector<T> resCoeffs( lh.formal_degree() + rh.formal_degree() + 1 );
    for ( auto i : range( lh.formal_degree() + 1 ) )
        for ( auto j : range( rh.formal_degree() + 1 ) )
            resCoeffs[i + j] += lh.get_coefficient( i ) * rh.get_coefficient( j );
    return Polynomial<T>( resCoeffs );
}