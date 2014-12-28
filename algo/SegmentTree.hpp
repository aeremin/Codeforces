#pragma once
#include <iterator>
#include <cassert>
#include <vector>

using std::vector;

template<class RandomAccessIterator, class Function>
class SegmentTree
{
public:
    typedef typename RandomAccessIterator::value_type ValueType;

public:
    SegmentTree(RandomAccessIterator first, RandomAccessIterator last, Function f) : first_(first), last_(last), f_(f)
    {
        valuesHeap_.resize((1 << calcHeight_(first, last)) - 1);
        build_(first, last, 0);
    }

    void update(RandomAccessIterator iter)
    {
        update_(iter, 0, first_, last_);
    }

    ValueType getValueOnSegment(RandomAccessIterator left, RandomAccessIterator right) const
    {
        return calcValueOnSegment_(left, right, 0, first_, last_);
    }

private:
    void build_(RandomAccessIterator left, RandomAccessIterator right, size_t ind)
    {
        if (right - left == 1)
        {
            valuesHeap_[ind] = *left;
        }
        else
        {
            auto center = left + (right - left) / 2;
            build_(left, center, leftChild_(ind));
            build_(center, right, rightChild_(ind));
            valuesHeap_[ind] = f_(valuesHeap_[leftChild_(ind)], valuesHeap_[rightChild_(ind)]);
        }
    }

    ValueType calcValueOnSegment_(RandomAccessIterator segmentLeft, RandomAccessIterator segmentRight,
                     size_t nodeInd, RandomAccessIterator nodeLeft, RandomAccessIterator nodeRight) const
    {
        assert(segmentLeft >= nodeLeft);
        assert(segmentRight <= nodeRight);
        
        if (segmentLeft == nodeLeft && segmentRight == nodeRight)
            return valuesHeap_[nodeInd];
        
        auto nodeCenter = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (nodeCenter >= segmentRight)
            return calcValueOnSegment_(segmentLeft, segmentRight, leftChild_(nodeInd), nodeLeft, nodeCenter);

        if (nodeCenter <= segmentLeft)
            return calcValueOnSegment_(segmentLeft, segmentRight, rightChild_(nodeInd), nodeCenter, nodeRight);

        return f_(calcValueOnSegment_(segmentLeft, nodeCenter, leftChild_(nodeInd), nodeLeft, nodeCenter),
                  calcValueOnSegment_(nodeCenter, segmentRight, rightChild_(nodeInd), nodeCenter, nodeRight));
    }

    void update_(RandomAccessIterator changed, size_t nodeInd, RandomAccessIterator nodeLeft, RandomAccessIterator nodeRight)
    {
        assert(changed >= nodeLeft);
        assert(changed <  nodeRight);

        if (nodeRight - nodeLeft == 1)
        {
            valuesHeap_[nodeInd] = *changed;
        }
        else
        {
            auto nodeCenter = nodeLeft + (nodeRight - nodeLeft) / 2;
            if (changed < nodeCenter)
                update_(changed, leftChild_(nodeInd), nodeLeft, nodeCenter);
            else
                update_(changed, rightChild_(nodeInd), nodeCenter, nodeRight);
            valuesHeap_[nodeInd] = f_(valuesHeap_[leftChild_(nodeInd)], valuesHeap_[rightChild_(nodeInd)]);
        }
    }


    static size_t leftChild_(size_t ind) { return 2 * ind + 1; }
    static size_t rightChild_(size_t ind) { return 2 * ind + 2; }

    int calcHeight_(RandomAccessIterator first, RandomAccessIterator last) const
    {
        auto length = std::distance(first, last);
        int result = 1;
        size_t maxLen = 1;
        while (length > maxLen)
        {
            maxLen *= 2;
            result++;
        }
        return result;
    }

private:
    const RandomAccessIterator first_, last_;
    const Function f_;

    vector<ValueType> valuesHeap_;
};