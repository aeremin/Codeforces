#pragma once

namespace update_types {

template <typename T>
struct SetTo {
  public:
    typedef T ValueType;

    SetTo() : isId_(true){};
    SetTo(T value) : isId_(false), value_(std::move(value)) {}

    friend SetTo<T> operator*(const SetTo<T>& lh, const SetTo<T>& rh) { return lh.isId_ ? rh : lh; }

  public:
    bool isId_;
    T value_;
};

}  // namespace update_types