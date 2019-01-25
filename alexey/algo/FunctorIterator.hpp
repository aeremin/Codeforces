#pragma once
#include <functional>
#include <iterator>

template <typename IntegerType, class Functor>
class FunctorIterator {
  private:
    IntegerType i_;
    std::reference_wrapper<Functor> f_;

  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename std::result_of<Functor(IntegerType)>::type value_type;
    typedef IntegerType difference_type;
    typedef IntegerType distance_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    FunctorIterator(IntegerType i, Functor& f) : i_(i), f_(f) {}

    auto operator*() const -> value_type { return f_(i_); }
    auto operator[](size_t offs) const -> value_type { return f_(i_ + offs); }

    const FunctorIterator& operator++() {
        ++i_;
        return *this;
    }
    const FunctorIterator& operator--() {
        --i_;
        return *this;
    }

    const FunctorIterator& operator+=(IntegerType v) {
        i_ += v;
        return *this;
    }
    const FunctorIterator& operator-=(IntegerType v) {
        i_ -= v;
        return *this;
    }

    IntegerType operator-(const FunctorIterator<IntegerType, Functor>& other) const { return i_ - other.i_; }
    bool operator==(const FunctorIterator<IntegerType, Functor>& other) const { return i_ == other.i_; }
    bool operator!=(const FunctorIterator<IntegerType, Functor>& other) const { return i_ != other.i_; }
    bool operator<(const FunctorIterator<IntegerType, Functor>& other) const { return i_ < other.i_; }
    bool operator>(const FunctorIterator<IntegerType, Functor>& other) const { return i_ > other.i_; }

    IntegerType getParameter() const { return i_; }
};

template <typename IntegerType, class Functor>
FunctorIterator<IntegerType, Functor> makeFunctorIterator(IntegerType i, Functor& f) {
    return FunctorIterator<IntegerType, Functor>(i, f);
}