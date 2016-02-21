#pragma once

namespace updateTypes
{

template<typename T>
struct LinearTransform
{
public:
    LinearTransform(T a = { 1 }, T b = { 0 }) : a_(std::move(a)), b_(std::move(b)) {}

    friend LinearTransform operator*(const LinearTransform& lh, const LinearTransform& rh)
    {
        return{ lh.a_ * rh.a_, lh.b_ + lh.a_ * rh.b_ };
    }

    T a_, b_;
};

}