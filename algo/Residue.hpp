#pragma once
#include <cstdint>

template<int64_t MOD>
class Residue
{
public:
    Residue( int64_t from = 0 )
    {
        int64_t remainder = from % MOD;
        if ( remainder < 0 )
            remainder += MOD;
        rep_ = remainder;
    }

    Residue<MOD> operator++( int )    {  return *this = Residue( rep_ + 1 );  }
    Residue<MOD> operator++( )    {  return *this = Residue( rep_ + 1 );  }
    Residue<MOD> operator--( int )    {  return *this = Residue( rep_ - 1 );  }
    Residue<MOD> operator--( )    {  return *this = Residue( rep_ - 1 );  }

    Residue<MOD> operator+=( Residue<MOD> v )    {  return *this = Residue( rep_ + v.rep() );  }
    Residue<MOD> operator-=( Residue<MOD> v )    {  return *this = Residue( rep_ - v.rep() );  }
    Residue<MOD> operator*=( Residue<MOD> v )    {  return *this = Residue( rep_ * v.rep() );  }

    int64_t rep() const { return rep_; }

private:
    int64_t rep_;
};

template<int64_t MOD>
Residue<MOD> operator+( Residue<MOD> a, Residue<MOD> b ) { return a += b; }

template<int64_t MOD>
Residue<MOD> operator-( Residue<MOD> a, Residue<MOD> b ) { return a -= b; }

template<int64_t MOD>
Residue<MOD> operator*( Residue<MOD> a, Residue<MOD> b ) { return a *= b; }

template<int64_t MOD>
Residue<MOD> operator+( Residue<MOD> a, int64_t b ) { return a += b; }

template<int64_t MOD>
Residue<MOD> operator-( Residue<MOD> a, int64_t b ) { return a -= b; }

template<int64_t MOD>
Residue<MOD> operator*( Residue<MOD> a, int64_t b ) { return a *= b; }

template<int64_t MOD>
std::ostream& operator<<( std::ostream& outStream, Residue<MOD> a ) {return outStream << a.rep();}
