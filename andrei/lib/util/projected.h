#pragma once

#include <utility>


template<typename Projector, typename Comparator>
class Projected {
public:
    Projected(Projector projector, Comparator comparator)
    : projector_(std::move(projector)), comparator_(std::move(comparator)) {}

    template<typename T>
    bool operator()(const T& a, const T& b) {
        return comparator_(projector_(a), projector_(b));
    }

private:
    Projector projector_;
    Comparator comparator_;
};

template<typename Projector>
class Projected<Projector, void> {
public:
    explicit Projected(Projector projector) : projector_(std::move(projector)) {}

    template<typename T>
    bool operator()(const T& a, const T& b) {
        return projector_(a) < projector_(b);
    }

private:
    Projector projector_;
};


template<typename Projector>
Projected<Projector, void> projected(Projector projector) {
    return Projected<Projector, void>(std::move(projector));
}

template<typename Projector, typename Comparator>
Projected<Projector, Comparator> projected(Projector projector, Comparator comparator) {
    return {std::move(projector), std::move(comparator)};
}
