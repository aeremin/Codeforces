#pragma once

class Solver487D
{
public:
    int main();

private:
    
    struct Place
    {
        int x, y;
        int ind() const;
        bool isFinal() const;
        void apply(char c);
        int block() const;
    };

    struct Query
    {
        char type;
        Place place;
        char dir;
    };

    vector<char> table;
    vector<Place> to;
    vector<Query> queries;

    static int tableWidth, tableHeight;
    static int blockHeight;

    void update(const Place from);
};
