#pragma once
#include <cstdint>
#include <cassert>
#include "algo/GreatestCommonDivisor.hpp"

template<typename UnderlyingInt, UnderlyingInt MOD>
class Residue
{
public:
    Residue(UnderlyingInt from = 0)
    {
        UnderlyingInt remainder = from % MOD;
        if ( remainder < 0 )
            remainder += MOD;
        rep_ = remainder;
    }

    bool operator==(Residue<UnderlyingInt, MOD> other) const { return rep_ == other.rep_; }
    
    Residue<UnderlyingInt, MOD> operator++(int)    { return *this = Residue(rep_ + 1); }
    Residue<UnderlyingInt, MOD> operator++()    { return *this = Residue(rep_ + 1); }
    Residue<UnderlyingInt, MOD> operator--(int)    { return *this = Residue(rep_ - 1); }
    Residue<UnderlyingInt, MOD> operator--()    { return *this = Residue(rep_ - 1); }

    Residue<UnderlyingInt, MOD> operator+=(Residue<UnderlyingInt, MOD> v)    { return *this = Residue(rep_ + v.rep()); }
    Residue<UnderlyingInt, MOD> operator-=(Residue<UnderlyingInt, MOD> v)    { return *this = Residue(rep_ - v.rep()); }
    Residue<UnderlyingInt, MOD> operator*=(Residue<UnderlyingInt, MOD> v)    { return *this = Residue(rep_ * v.rep()); }

    Residue<UnderlyingInt, MOD> inversed() const
    {
        int64_t x, y;
        auto gcd = gcdDecomposition( rep_, MOD, x, y );
        assert( gcd == 1 );
        return{ x };
    }

    UnderlyingInt rep() const { return rep_; }

private:
    UnderlyingInt rep_;
};

template<typename UnderlyingInt, UnderlyingInt MOD>
Residue<UnderlyingInt, MOD> operator+(Residue<UnderlyingInt, MOD> a, Residue<UnderlyingInt, MOD> b) { return a += b; }

template<typename UnderlyingInt, UnderlyingInt MOD>
Residue<UnderlyingInt, MOD> operator-(Residue<UnderlyingInt, MOD> a, Residue<UnderlyingInt, MOD> b) { return a -= b; }

template<typename UnderlyingInt, UnderlyingInt MOD>
Residue<UnderlyingInt, MOD> operator*(Residue<UnderlyingInt, MOD> a, Residue<UnderlyingInt, MOD> b) { return a *= b; }

template<typename UnderlyingInt, UnderlyingInt MOD>
Residue<UnderlyingInt, MOD> operator+(Residue<UnderlyingInt, MOD> a, UnderlyingInt b) { return a += b; }

template<typename UnderlyingInt, UnderlyingInt MOD>
Residue<UnderlyingInt, MOD> operator-(Residue<UnderlyingInt, MOD> a, UnderlyingInt b) { return a -= b; }

template<typename UnderlyingInt, UnderlyingInt MOD>
Residue<UnderlyingInt, MOD> operator*(Residue<UnderlyingInt, MOD> a, UnderlyingInt b) { return a *= b; }

template<typename UnderlyingInt, UnderlyingInt MOD>
std::ostream& operator<<(std::ostream& outStream, Residue<UnderlyingInt, MOD> a) { return outStream << a.rep(); }

using CodeforcesResidue = Residue<int, 1000000007>;

using CodeforcesResidue64 = Residue<int64_t, 1000000007>;