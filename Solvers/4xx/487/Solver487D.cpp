#include "Solvers/pch.h"
#include "Solver487D.h"

// TODO: Get rid of static class members
int Solver487D::tableHeight = 0;
int Solver487D::tableWidth = 0;
int Solver487D::blockHeight = 0;

bool Solver487D::Place::isFinal() const
{
    return (x <= 0) || (y <= 0) || (x == tableWidth + 1);
}

int Solver487D::Place::ind() const
{
    return x + ((tableWidth + 2) * y);
}

void Solver487D::Place::apply(char c)
{
    switch (c)
    {
    case '<':
        x--;
        break;
    case '>':
        x++;
        break;
    case '^':
        y--;
        break;
    }
}

int Solver487D::Place::block() const
{
    return ((y - 1) / blockHeight) + 1;
}

void Solver487D::update(const Place from)
{
    Place cur = from;
    bool lost = false;
    char dir = ' ';
    char prevDir = ' ';
    int timeout = 0;
    while (!cur.isFinal() && cur.y == from.y && !lost)
    {
        dir = table[cur.ind()];
        lost = (dir == '<' && prevDir == '>') || (dir == '>' && prevDir == '<');
        cur.apply(dir);
        prevDir = dir;
        assert(timeout++ < tableWidth + 1);
    }

    if (lost)
    {
        cur.x = -1; cur.y = -1;
        to[from.ind()] = cur;
    }
    else if (cur.isFinal())
    {
        to[from.ind()] = cur;
    }
    else if (cur.block() == from.block())
    {
        to[from.ind()] = to[cur.ind()];
    }
    else
    {
        to[from.ind()] = cur;
    }
}


int Solver487D::main()
{

    int nQueries;
    cin >> tableHeight >> tableWidth >> nQueries;

    int maxInd = (tableWidth + 2) * (tableHeight + 1);
    table.resize(maxInd);

    Place cur;
    for (cur.y = 1; cur.y <= tableHeight; cur.y++)
        for (cur.x = 1; cur.x <= tableWidth; cur.x++)
            cin >> table[cur.ind()];

    to.resize(maxInd);

    int aQueries = 0;
    int cQueries = 0;
    for (int iQuery = 0; iQuery < nQueries; ++iQuery)
    {
        Query q;
        cin >> q.type >> q.place.y >> q.place.x;
        if (q.type == 'A')
        {
            aQueries++;
        }
        else
        {
            cQueries++;
            cin >> q.dir;
        }
        queries.push_back(q);
    }

    blockHeight = int( max(sqrt((double(aQueries) * tableHeight) / (cQueries * tableWidth * 5)), 1.1) );

    for (cur.y = 1; cur.y <= tableHeight; cur.y++)
        for (cur.x = 1; cur.x <= tableWidth; cur.x++)
            update(cur);

    for (int iQuery = 0; iQuery < nQueries; ++iQuery)
    {
        Query& q = queries[iQuery];
        cur = q.place;
        if (q.type == 'A')
        {
            while (!cur.isFinal()) cur = to[cur.ind()];
            cout << cur.y << " " << cur.x << "\n";
        }
        else
        {
            table[cur.ind()] = q.dir;
            int minHeight = cur.y;
            int maxHeight = min(cur.block() * blockHeight, tableHeight);
            Place upd;
            for (upd.y = minHeight; upd.y <= maxHeight; ++upd.y)
                for (upd.x = 1; upd.x <= tableWidth; ++upd.x)
                    update(upd);
        }

    }

    return 0;
}

class Solver487DTest : public ProblemTest {};

static std::string input1 = R"(4 5 7
><<^<
^<^^>
>>>^>
>^>>^
A 3 1
A 2 2
C 1 4 <
A 3 1
C 1 2 ^
A 3 1
A 2 2)";

static std::string output1 = R"(0 4
-1 -1
-1 -1
0 2
0 2
)";

TEST_F(Solver487DTest, Example1)
{
    setInput(input1);
    Solver487D().main();
    EXPECT_EQ(output1, getOutput());
}

TEST_F(Solver487DTest, Example2)
{
    setInput(R"(2 2 3
>>
^^
A 2 1
C 1 2 <
A 2 1)");
    Solver487D().main();
    EXPECT_EQ("1 3\n-1 -1\n", getOutput());
}