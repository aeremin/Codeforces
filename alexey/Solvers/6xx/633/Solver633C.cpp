#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/strings/knutt_morris_pratt.h"
#include "algo/io/readvector.hpp"
#include "algo/strings/trie.h"

using namespace std;

class Solver633C
{
public:
    void run();

    vector<int> allowedFinishes( string pattern, const string& ciphered )
    {
        transform( pattern.begin(), pattern.end(), pattern.begin(), ::tolower );
        reverse( pattern.begin(), pattern.end() );
        string s = pattern + "$" + ciphered;
        auto pi = PrefixFunction( s );
        vector<int> result;
        for ( int i : range( ciphered.length() ) )
            if ( pi[pattern.length() + 1 + i] == pattern.length() )
                result.push_back( i );
        return result;
    }

};

void Solver633C::run()
{
    int len;
    cin >> len;
    string ciphered;
    cin >> ciphered;
    int dictionarySize;
    cin >> dictionarySize;
    vector<string> dictionary = readVector<string>( dictionarySize );
    unordered_map<string, string> decipherer;
    Trie trie;
    for (const auto& word : dictionary) {
        string wordLowCase;
        transform(word.begin(), word.end(), back_inserter(wordLowCase), ::tolower);
        decipherer.insert({ wordLowCase, word });
        trie.AddWord(wordLowCase + "\n");
    }

    vector<string> jumps(len + 1, "");
    jumps[0] = "\n";
    
    for (int i : range(len)) {
        string currWord;
        size_t currNode = 0;
        for (int j = i; j >= 0; --j) {
            currWord.push_back(ciphered[j]);
            currNode = trie.traverse(currNode, ciphered[j]);
            if (currNode == Trie::InvalidIndex)
                break;
            if (trie.traverse(currNode, '\n') != Trie::InvalidIndex && !jumps[j].empty()) {
                jumps[i + 1] = currWord;
                break;
            }
        }
    }

    deque<string> words;
    int currPos = len;
    do
    {
        auto word = jumps[currPos];
        words.push_front(word);
        currPos -= word.length();
    } while ( currPos > 0 );

    for ( auto w : words)
        cout << decipherer[w] << " ";
}

class Solver633CTest : public ProblemTest {};

TEST_F(Solver633CTest, Example1)
{
    string input = R"(30
ariksihsidlihcdnaehsetahgnisol
10
Kira
hates
is
he
losing
death
childish
L
and
Note
)";
    string output = R"(Kira is childish and he hates losing 
)";
    setInput(input);
    Solver633C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver633CTest, Example2)
{
    string input = R"(12
iherehtolleh
5
HI
Ho
there
HeLLo
hello
)";
    string output = R"(HI there HeLLo 
)";
    setInput(input);
    Solver633C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F( Solver633CTest, MaxCase )
{
    stringstream ss;
    ss << "10000\n";
    ss << string( 10000, 'a' ) << "\n";
    ss << "1000\n";
    for ( int i : range( 1, 1001 ) )
        ss << string( i, 'a' ) << "\n";
    
    setInput( ss.str() );
    Solver633C().run();
}


