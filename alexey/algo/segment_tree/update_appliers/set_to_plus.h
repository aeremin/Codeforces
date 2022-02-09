#pragma once
#include "update_applier.h"
#include "algo/segment_tree/update_types/set_to.h"

template <typename T>
struct UpdateApplier<update_types::SetTo<T>, std::plus<T>> {
    static T apply(const T& v, const update_types::SetTo<T>& upd, size_t length) {
        return upd.isId_ ? v : upd.value_ * length;
    }
};
