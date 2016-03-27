#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "iter/range.h"

class SuffixAutomaton {
public:
    struct State {
        std::unordered_map<char, int> edges;
        int len, link;
        int size;
        bool isFinal;
    };
    
    SuffixAutomaton(const std::string& s) {
        states_.push_back(State{ std::unordered_map<char, int>{}, 0, -1, 1, false });
        int last = 0;
        for (auto c : s)
            last = append(c, last);

        for (int i = last; i != -1; i = states_[i].link)
            states_[i].isFinal = true;

        std::vector<std::vector<int>> statesPerLen(s.length() + 1);
        for (int i : range(states_.size()))
            statesPerLen[states_[i].len].push_back(i);
        for (auto it = statesPerLen.rbegin(); it != statesPerLen.rend(); ++it)
            for (auto ind : *it)
                if (states_[ind].link != -1)
                    states_[states_[ind].link].size += states_[ind].size;
    }

    int traverse(const std::string& s, int stateIndex = 0) const {
        for (auto c : s)
            stateIndex = traverse(c, stateIndex);
        return stateIndex;
    }
    
    int traverse(char c, int stateIndex) const {
        if (stateIndex == -1) return -1;
        auto itNext = states_[stateIndex].edges.find(c);
        if (itNext != end(states_[stateIndex].edges))
            return itNext->second;
        else
            return -1;
    }
    
    int getSize(int stateIndex) const              {    return states_[stateIndex].size;                           }

    bool isFinal(int stateIndex) const             {    return stateIndex != -1 && states_[stateIndex].isFinal;    }

    const std::vector<State>& getStates() const    {    return states_;              }

    bool isSubstring(const std::string& s) const   {    return traverse(s) != -1;    }
    bool isSuffix(const std::string& s) const      {    return isFinal(traverse(s)); }

private:


    int append(char c, int last) {
        // We add new state corresponding to s + c
        // It will has index curr.
        int curr = states_.size();
        states_.push_back(State{ std::unordered_map<char, int>{}, states_[last].len + 1, -2, 1, false });
        
        int p = last;
        while (p != -1 && states_[p].edges.count(c) == 0) {
            states_[p].edges[c] = curr;
            p = states_[p].link;
        }
        if (p == -1)
            states_[curr].link = 0;
        else {
            int q = states_[p].edges.at(c);
            if (states_[p].len + 1 == states_[q].len) // (p, q) is solid edge
                states_[curr].link = q;
            else {
                int clone = states_.size();           // (p, q) is not solid,
                states_.push_back(states_[q]);        // we do a split q ---> clone, q
                states_[clone].len = states_[p].len + 1;
                states_[clone].size = 0;
                states_[curr].link = clone;
                states_[q].link = clone;
                for (; p != -1; p = states_[p].link) {
                    auto it = states_[p].edges.find(c);
                    if (it != end(states_[p].edges) && it->second == q)
                        it->second = clone;
                    else
                        break;
                }
            }
        }

        assert(states_[curr].link != -2);
        return curr;
    }

    std::vector<State> states_;
};