#pragma once
#include "algo/updateappliers/UpdateApplier.hpp"

template <typename T>
struct UpdateApplier<updateTypes::IncreaseBy<T>, std::plus<T>> {
    static T apply(const T& v, const updateTypes::IncreaseBy<T>& upd, size_t cnt) { return v + cnt * upd.value_; }
};
