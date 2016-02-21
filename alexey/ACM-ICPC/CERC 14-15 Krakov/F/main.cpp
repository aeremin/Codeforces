#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <cstdint>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef int64_t ll;

struct Matrix
{
    Matrix() : d(3, vector<ll>(3, 0))
    {}

    ll sum() const
    {
        ll res = 0;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                res += d[i][j];
            }
        return res;
    }

    const Matrix& operator+=(const Matrix& r)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                d[i][j] += r.d[i][j];
            }
        return *this;
    }

    vector<vector<ll>> d;
};


vector<vector<vector<Matrix>>> indic(28, vector<vector<Matrix>>(28, vector<Matrix>(28)));
vector<char> possibleSymbols;

Matrix& getMat(char a, char b, char c)
{
    int i1 = (a == '?') ? 27 : a - 'a' + 1;
    int i2 = (b == '?') ? 27 : b - 'a' + 1;
    int i3 = (c == '?') ? 27 : c - 'a' + 1;
    return indic[i1][i2][i3];
}

inline int ind(char a, char b)
{
    if (a < b)
        return 0;
    if (a == b)
        return 1;
    return 2;
}

inline char getStr(string& s, int ind)
{
    if (ind >= s.length())
        return 'a' - 1;
    return s[ind];
}


bool real(char a)
{
    return a != 'a' - 1;
}
int main()
{
    freopen("f.in", "rt", stdin);
    freopen("f.out", "wt", stdout);
    cout << 1<<endl;
    cout << 1000<<endl;
    for (int i = 1; i < 1000; i++) cout << i << " " << i/9 << endl;
    cout << (1000 * 999 / 2) <<endl;
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            if (i<j)
            cout << i << " " << j << endl;
    return 0;
    const ll MODULO = 1e9 + 9.1;

    possibleSymbols.push_back('a' - 1);
    for (auto c = 'a'; c <= 'z'; ++c)
        possibleSymbols.push_back(c);

    for (char a : possibleSymbols)
        for (char b : possibleSymbols)
            for (char c : possibleSymbols)
            {
                Matrix m;
                m.d[ind(a, b)][ind(b, c)] = 1;
                getMat(a, b, c) += m;

                if (real(a)) getMat('?', b, c) += m;
                if (real(b)) getMat(a, '?', c) += m;
                if (real(c)) getMat(a, b, '?') += m;

                if (real(a) && real(b)) getMat('?', '?', c) += m;
                if (real(b) && real(c)) getMat(a, '?', '?') += m;
                if (real(a) && real(c)) getMat('?', b, '?') += m;

                if (real(a) && real(b) && real(c)) getMat('?', '?', '?') += m;
            }

    possibleSymbols.push_back('?');

    int nTests;
    cin >> nTests;

    for (int iTest = 0; iTest < nTests; ++iTest)
    {
        ll a00 = 1;
        ll a01 = 0;
        ll a10 = 0;
        ll a11 = 0;

        ll b00, b11, b10, b01;
        string w1, w2, w3;
        cin >> w1 >> w2 >> w3;

        
        int len = max(max(w1.length(), w2.length()), w3.length());
        for (int i = 0; i < len; ++i)
        {
            char a = getStr(w1, i);
            char b = getStr(w2, i);
            char c = getStr(w3, i);

            Matrix& m = getMat(a, b, c);

            b00 = (m.d[1][1] * a00) % MODULO;
            b01 = (m.d[1][1] * a01 + m.d[1][0] * (a01 + a00) + m.d[1][2] * a01) % MODULO;
            b10 = (m.d[1][1] * a10 + m.d[0][1] * (a10 + a00) + m.d[2][1] * a10) % MODULO;
            b11 = (m.d[1][0] * a10 + m.d[0][0] * (a00 + a01 + a10) + m.d[2][0] * a10 + m.d[0][1] * a01 + m.d[0][2] * a01 + m.sum() * a11) % MODULO;

            swap(a00, b00);
            swap(a01, b01);
            swap(a10, b10);
            swap(a11, b11);
        }
        cout << a11 << endl;
    }



    return 0;
}

