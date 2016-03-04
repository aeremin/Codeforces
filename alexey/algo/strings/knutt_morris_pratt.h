#pragma once
#include <vector>

// Time complexity is O( s.size() ).
// Can be applied to any STL-style container (including std::string).
template<class Container>
std::vector<int> PrefixFunction( const Container& s )
{
	vector<int> pi;
	if (s.empty())
		return pi;
    pi.push_back( 0 );
    for ( auto it = begin( s ) + 1; it != end( s ); ++it )
	{
        auto& elt = *it;
        int curPi = pi.back();
        while ( curPi > 0 && elt != s[curPi] )
			curPi = pi[curPi - 1];
        if ( elt == s[curPi] ) curPi++;
		pi.push_back(curPi);
	}
	return pi;
}