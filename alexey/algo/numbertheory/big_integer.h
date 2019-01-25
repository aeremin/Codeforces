#pragma once
#include <numeric>
#include <vector>

#include "iter/range.h"

class BigInteger {
  public:
    BigInteger() {}

    BigInteger(uint64_t a) { add_to_front(a); }

    int len() const { return digits_.size(); }

    int at(int position) const { return (position < digits_.size() && position >= 0) ? digits_[position] : 0; }

    int DigitsSum() const { return std::accumulate(begin(digits_), end(digits_), 0); }

    const BigInteger& operator+=(const BigInteger& other) {
        if (other.digits_.size() > digits_.size())
            digits_.resize(other.digits_.size());
        uint64_t over = 0;
        for (int i : range(digits_.size())) {
            over += at(i) + other.at(i);
            digits_[i] = over % 10;
            over /= 10;
        }
        add_to_front(over);
        return *this;
    }

    friend BigInteger operator*(const BigInteger& lh, const BigInteger& rh) {
        BigInteger res;
        uint64_t over = 0;
        for (int pos : range(lh.digits_.size() + rh.digits_.size() - 1)) {
            for (int i : range(pos + 1))
                over += lh.at(i) * rh.at(pos - i);
            res.digits_.push_back(over % 10);
            over /= 10;
        }
        res.add_to_front(over);
        return res;
    }

    bool operator==(const BigInteger& other) const { return digits_ == other.digits_; }

    friend std::ostream& operator<<(std::ostream& outStream, const BigInteger& a) {
        for (auto it = a.digits_.rbegin(); it != a.digits_.rend(); ++it)
            outStream << int(*it);
        return outStream;
    }

  private:
    void add_to_front(uint64_t a) {
        while (a) {
            digits_.push_back(a % 10);
            a /= 10;
        }
    }

  private:
    std::vector<uint8_t> digits_;
};