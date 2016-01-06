#pragma once
#include <vector>

using std::vector;
using std::swap;

class DisjointSet
{
public:
    DisjointSet(int size) : rank_(size, 0), parent_(size)
    {
        for (int i = 0; i < size; ++i)
            parent_[i] = i;

        componentsCount_ = size;
    }

    int rep(int elt)
    {
        if (parent_[elt] == elt)
        {
            return elt;
        }
        else
        {
            parent_[elt] = rep(parent_[elt]);
            return parent_[elt];
        }
    }

    bool inSameSet(int elt1, int elt2)
    {
        return (rep(elt1) == rep(elt2));
    }

    void unionSets(int elt1, int elt2)
    {
        auto rep1 = rep(elt1);
        auto rep2 = rep(elt2);
        if (rep1 != rep2)
        {
            if (rank_[rep1] < rank_[rep2])
                swap(rep1, rep2);
            parent_[rep2] = rep1;
            if (rank_[rep1] == rank_[rep2])
                rank_[rep1]++;
            --componentsCount_;
        }
    }

    int getComponentsCount() const
    {
        return componentsCount_;
    }

private:
    vector<int> rank_;
    vector<int> parent_;
    int componentsCount_;
};