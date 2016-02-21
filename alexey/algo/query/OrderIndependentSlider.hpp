#pragma once

// MultiSetCalculator should have following types defined:
// InType, OutType
//
// and provide following methods:
// void inser(InType), void erast(InType) and OutType value(),
// and void reset();

template<class MultiSetCalculator>
class OrderIndependentSlider
{
public:
    using OutType = typename MultiSetCalculator::OutType;
    using InType = typename MultiSetCalculator::InType;

    OrderIndependentSlider(MultiSetCalculator calc = {}) : calc_(calc) {};
    
    void push_back(const InType& a) { calc_.insert(a); }
    void push_front(const InType& a) { calc_.insert(a); }
    void pop_front(const InType& a) { calc_.erase(a); }

    OutType value() const { return calc_.value(); }

    void reset() { calc_.reset(); }

private:
    MultiSetCalculator calc_;
};