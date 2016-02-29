#pragma  once
#include <vector>
#include <unordered_map>
#include <string>

class Trie {
public:
    enum { InvalidIndex = -1 };

    Trie() : nodes_(1) {}

    // Complexity is O(s.length()).
    // Returns index of the word end node.
    size_t AddWord(const std::string& s) {
        size_t curr = 0;
        for (auto c : s) {
            auto next = traverse(curr, c);
            if (next == InvalidIndex) {
                next = nodes_.size();
                nodes_.emplace_back();
                nodes_[curr].insert({ c, next });
            }
            curr = next;
        }
        return curr;
    }
    
    // Average complexity is O(1).
    size_t traverse(size_t from, char c) const {
        auto iter = nodes_[from].find(c);
        return (iter == end(nodes_[from])) ? InvalidIndex : iter->second;
    }

private:
    std::vector<std::unordered_map<char, size_t>> nodes_;
};
