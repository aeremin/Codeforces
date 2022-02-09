#pragma once

template <typename T>
T indicator(bool v) {
    return v ? T(1) : T(0);
}