#pragma once
#include <vector>

#include "algo/SortWithMapping.hpp"
#include "algo/geometry/geomvector.hpp"

template <typename T>
void angleSort(std::vector<GeomVector2<T>>& data, std::vector<size_t>* forwardMapping,
               std::vector<size_t>* reverseMapping) {
    auto zero = T(0);

    auto inFirstSemicircle = [&](const GeomVector2<T>& v) -> bool {
        return v[1] > zero || (v[1] == zero && v[0] > zero);
    };

    auto anglePredicate = [&](const GeomVector2<T>& v1, const GeomVector2<T>& v2) -> bool {
        bool s1 = inFirstSemicircle(v1);
        bool s2 = inFirstSemicircle(v2);
        if (s1 && !s2)
            return true;
        if (s2 && !s1)
            return false;

        return det(v1, v2) > zero;
    };

    sortWithMappings(data, anglePredicate, forwardMapping, reverseMapping);
}