#pragma once
#include <cstdint>

template <size_t NBits>
class FullBinaryTrie {
  public:
    FullBinaryTrie() : isNodePresent_((uint64_t(1) << (NBits + 1)) - 1, 0){};

    void insert(uint64_t value) {
        auto node = getLeafByValue_(value);
        while (isNodePresent_[node] == 0) {
            isNodePresent_[node] = 1;
            if (node != 0)
                node = parent_(node);
            else
                break;
        }
    }

    void erase(uint64_t value) {
        auto node = getLeafByValue_(value);
        assert(isNodePresent_[node]);
        do {
            isNodePresent_[node] = 0;
            if (node == 0)
                break;
            node = parent_(node);
        } while (!hasAnyChild_(node));
    }

    bool has(uint64_t value) const { return isNodePresent_[getLeafByValue_(value)]; }

    template <class Traversor>
    std::pair<bool, uint64_t> traverse(Traversor& traversor) const {
        auto currentPowerOfTwo = uint64_t(1) << NBits - 1;
        uint64_t currentValue = 0;

        size_t node = 0;
        while (!isLeaf_(node)) {
            std::pair<bool, int> traversorAnswer = traversor(hasChild(node, 0), hasChild(node, 1));
            if (!traversorAnswer.first)
                return {false, currentValue};
            currentValue += traversorAnswer.second * currentPowerOfTwo;
            currentPowerOfTwo /= 2;
            node = child_(node, traversorAnswer.second);
        }

        return {true, currentValue};
    }


  private:
    size_t getLeafByValue_(uint64_t value) const { return value + (uint64_t(1) << NBits) - 1; }
    bool isLeaf_(size_t node) const { return node >= (uint64_t(1) << NBits) - 1; }
    size_t child_(size_t node, int bit) const { return 2 * node + bit + 1; }
    bool hasChild(size_t node, int bit) const { return !isLeaf_(node) && isNodePresent_[child_(node, bit)] != 0; }
    bool hasAnyChild_(size_t node) const { return hasChild(node, 0) || hasChild(node, 1); }
    size_t parent_(size_t node) const { return (node - 1) / 2; }

  private:
    // char used instead of bool as std::vector<bool> is packed and slow
    std::vector<char> isNodePresent_;
};