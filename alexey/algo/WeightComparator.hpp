#pragma once

template<class WeightFunctor>
class WeightComparator
{
public:
    WeightComparator(WeightFunctor f) : f_(f) {}
    
    template<typename T>
    bool operator()(const T& lh, const T& rh) { return f_(lh) < f_(rh); }
private:
    WeightFunctor f_;
};

template<class WeightFunctor>
WeightComparator<WeightFunctor> makeWeightComparator(WeightFunctor f) { return WeightComparator<WeightFunctor>(f); }