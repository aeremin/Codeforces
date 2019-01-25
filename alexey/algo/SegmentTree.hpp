#pragma once
#include <cassert>
#include <iterator>
#include <vector>

using std::vector;

template <typename ValueType, class AggregatingFunction, class UpdateType>
class SegmentTree {
  public:
    SegmentTree(const vector<ValueType>& initialValues, AggregatingFunction aggregatingFunction)
        : aggregatingFunction_(aggregatingFunction), size_(initialValues.size()) {
        auto heapSize = (size_t(1) << calcHeight_(size_)) - 1;
        valuesHeap_.resize(heapSize);
        lazyUpdatesHeap_.resize(heapSize);
        build_(begin(initialValues), end(initialValues), 0);
    }

    void updateElement(size_t i, UpdateType upd) { updateRange(i, i + 1, upd); }

    void updateRange(size_t l, size_t r, UpdateType upd) {
        if (l == r)
            return;
        update_(l, r, upd, 0, 0, size_);
    }

    ValueType getValueOnSegment(size_t l, size_t r) const {
        return calcValueOnSegment_(l, r, UpdateType(), 0, 0, size_);
    }

  private:
    typedef typename vector<ValueType>::const_iterator Iterator;

    void build_(Iterator left, Iterator right, size_t ind) {
        if (right - left == 1) {
            valuesHeap_[ind] = *left;
        } else {
            auto center = left + (right - left) / 2;
            build_(left, center, leftChild_(ind));
            build_(center, right, rightChild_(ind));
            valuesHeap_[ind] = aggregatingFunction_(valuesHeap_[leftChild_(ind)], valuesHeap_[rightChild_(ind)]);
        }
    }

    void update_(size_t l, size_t r, const UpdateType& upd, size_t nodeInd, size_t nodeLeft, size_t nodeRight) {
        if (l == nodeLeft && r == nodeRight) {
            lazyUpdatesHeap_[nodeInd] = upd * lazyUpdatesHeap_[nodeInd];
            return;
        }

        lazyUpdatesHeap_[leftChild_(nodeInd)] = lazyUpdatesHeap_[nodeInd] * lazyUpdatesHeap_[leftChild_(nodeInd)];
        lazyUpdatesHeap_[rightChild_(nodeInd)] = lazyUpdatesHeap_[nodeInd] * lazyUpdatesHeap_[rightChild_(nodeInd)];
        lazyUpdatesHeap_[nodeInd] = UpdateType();

        auto nodeCenter = (nodeLeft + nodeRight) / 2;
        if (r <= nodeCenter) {
            update_(l, r, upd, leftChild_(nodeInd), nodeLeft, nodeCenter);
        } else if (l >= nodeCenter) {
            update_(l, r, upd, rightChild_(nodeInd), nodeCenter, nodeRight);
        } else {
            update_(l, nodeCenter, upd, leftChild_(nodeInd), nodeLeft, nodeCenter);
            update_(nodeCenter, r, upd, rightChild_(nodeInd), nodeCenter, nodeRight);
        }

        valuesHeap_[nodeInd] = aggregatingFunction_(
            calcValueOnSegment_(nodeLeft, nodeCenter, {}, leftChild_(nodeInd), nodeLeft, nodeCenter),
            calcValueOnSegment_(nodeCenter, nodeRight, {}, rightChild_(nodeInd), nodeCenter, nodeRight));
    }

    static size_t leftChild_(size_t ind) { return 2 * ind + 1; }
    static size_t rightChild_(size_t ind) { return 2 * ind + 2; }

    ValueType calcValueOnSegment_(size_t l, size_t r, UpdateType upd, size_t nodeInd, size_t nodeLeft,
                                  size_t nodeRight) const {
        assert(l >= nodeLeft);
        assert(r <= nodeRight);
        upd = upd * lazyUpdatesHeap_[nodeInd];
        if (l == nodeLeft && r == nodeRight)
            return UpdateApplier<UpdateType, AggregatingFunction>::apply(valuesHeap_[nodeInd], upd, r - l);

        auto nodeCenter = (nodeLeft + nodeRight) / 2;

        if (r <= nodeCenter)
            return calcValueOnSegment_(l, r, upd, leftChild_(nodeInd), nodeLeft, nodeCenter);
        else if (l >= nodeCenter)
            return calcValueOnSegment_(l, r, upd, rightChild_(nodeInd), nodeCenter, nodeRight);
        else
            return aggregatingFunction_(
                calcValueOnSegment_(l, nodeCenter, upd, leftChild_(nodeInd), nodeLeft, nodeCenter),
                calcValueOnSegment_(nodeCenter, r, upd, rightChild_(nodeInd), nodeCenter, nodeRight));
    }

    int calcHeight_(size_t length) const {
        int result = 1;
        size_t maxLen = 1;
        while (length > maxLen) {
            maxLen *= 2;
            result++;
        }
        return result;
    }

  private:
    const AggregatingFunction aggregatingFunction_;

    size_t size_;
    vector<ValueType> valuesHeap_;
    vector<UpdateType> lazyUpdatesHeap_;
};

template <typename ValueType, class AggregatingFunction, class UpdateType>
SegmentTree<ValueType, AggregatingFunction, UpdateType> makeSegmentTree(const vector<ValueType>& initialValues,
                                                                        AggregatingFunction aggregatingFunction,
                                                                        UpdateType dummy) {
    return SegmentTree<ValueType, AggregatingFunction, UpdateType>(initialValues, aggregatingFunction);
}