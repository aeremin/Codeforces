#pragma once
#include <utility>
#include <cassert>

// Solves quadratic equation in field of real numbers.
// result.first <= result.second
// Behavior is undefined in case if there is no roots (negative discriminant).
// a must not equal 0.
inline std::pair<double, double> solveQuadraticEquation(double a, double b, double c) {
    assert(a != 0);
    auto D = b * b - 4 * a * c;
    assert(D >= -1e-8); // To prevent issues with D being
    D = std::max(D, 0.0);    // slightly negative due to calculation errors
    auto rootD = sqrt(D);
    std::pair<double, double> res = { (-b - rootD) / (2 * a),  (-b + rootD) / (2 * a) };
    if (a < 0)
        std::swap(res.first, res.second);

    return res;
}