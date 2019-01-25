#pragma once
#include <functional>
#include <limits>
#include <unordered_map>
#include <vector>

#include "util/relax.h"


template <typename InType, typename OutType, int StatesCount>
class DPProcessor {
  public:
    typedef std::function<OutType(InType)> TransitionFunction;
    DPProcessor& addRule(int from, int to, TransitionFunction f) {
        rules_.emplace_back(from, to, f);
        return *this;
    }

    typedef std::vector<OutType> StatesCost;
    template <class Iterator>
    StatesCost process(StatesCost startState, Iterator l, Iterator r) const {
        for (; l != r; ++l)
            processOneInput_(startState, *l);
        return startState;
    }

  private:
    // Needed to minimize dynamic memory allocations
    mutable StatesCost tmp_ = StatesCost(StatesCount, std::numeric_limits<OutType>::max());
    void processOneInput_(StatesCost& state, const InType& in) const {
        fill(begin(tmp_), end(tmp_), std::numeric_limits<OutType>::max());
        for (auto& rule : rules_) {
            auto stateCost = state[std::get<0>(rule)];
            if (stateCost != std::numeric_limits<OutType>::max()) {
                auto ruleCost = std::get<2>(rule)(in);
                if (ruleCost != std::numeric_limits<OutType>::max()) {
                    auto ruleResultCost = stateCost + ruleCost;
                    auto ruleResultState = std::get<1>(rule);
                    relax_min(tmp_[ruleResultState], ruleResultCost);
                }
            }
        }
        std::swap(state, tmp_);
    }

    std::vector<std::tuple<int, int, TransitionFunction>> rules_;
};
