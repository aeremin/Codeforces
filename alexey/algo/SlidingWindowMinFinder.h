#pragma once

#include <deque>
#include <vector>

using namespace std;

template <class T, class Comparator = std::less<T>>
class SlidingWindowMinFinder {
  private:
    vector<T>& data_;
    deque<pair<T, int>> currentSet_;
    int left_;
    int right_;
    Comparator c_;

  public:
    SlidingWindowMinFinder(vector<T>& data) : data_(data), left_(0), right_(0) {}

    void incLeft() { left_++; }

    void incRight() {
        T newElt = data_[right_];
        while (!currentSet_.empty() && !c_(currentSet_.back().first, newElt))
            currentSet_.pop_back();
        currentSet_.push_back(make_pair(newElt, right_));
        right_++;
    }

    T getMin() {
        while (currentSet_.front().second < left_)
            currentSet_.pop_front();
        return currentSet_.front().first;
    }

    int getLeft() { return left_; }

    int getRight() { return right_; }
};
