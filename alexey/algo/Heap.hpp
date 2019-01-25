#pragma once

#include <cassert>
#include <utility>
#include <vector>
using std::swap;
using std::vector;

template <class T>
class Heap {
  public:
    bool isEmpty() const { return data.size() == 0; }

    const T& getMinElt() const {
        assert(!isEmpty());
        return data.front();
    }

    void push(const T& elt) {
        data.push_back(elt);
        int ind = data.size() - 1;
        int parentInd = parent(ind);
        while (parentInd >= 0 && data[parentInd] > data[ind]) {
            swap(data[ind], data[parentInd]);
            ind = parentInd;
            parentInd = parent(ind);
        }
    }

    bool popMin() {
        if (isEmpty())
            return false;
        data[0] = data.back();
        data.pop_back();
        int ind = 0;
        while (hasChild(ind)) {
            int minChildInd = ind;
            bool finished = true;
            for (int offs = 0; offs <= 1; ++offs) {
                int childInd = leftChild(ind) + offs;
                if (isValidInd(childInd) && data[childInd] < data[minChildInd]) {
                    minChildInd = childInd;
                    finished = false;
                }
            }
            if (finished)
                break;

            swap(data[ind], data[minChildInd]);
            ind = minChildInd;
        }

        return true;
    }

  private:
    static int leftChild(int ind) { return 2 * ind + 1; }
    static int parent(int ind) { return (ind - 1) / 2; }

    bool isValidInd(int ind) { return ind < data.size(); }
    bool hasChild(int ind) { return isValidInd(leftChild(ind)); }

  private:
    vector<T> data;
};
