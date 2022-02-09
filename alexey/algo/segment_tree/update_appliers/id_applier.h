#pragma once
#include "update_applier.h"
#include "algo/segment_tree/update_types/id.h"

template <typename Functor>
struct UpdateApplier<update_types::Id, Functor> {
    template <typename T>
    static T apply(const T& v, const update_types::Id&, size_t) {
        return v;
    }
};
