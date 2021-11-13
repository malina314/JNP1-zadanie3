#ifndef FUZZY_H
#define FUZZY_H

#include <compare>
#include <ostream>
#include <set>
#include <tuple>

using real_t = double;

class TriFuzzyNum {
    real_t l;
    real_t m;
    real_t u;

    const std::tuple<real_t, real_t, real_t> getRank() const;

    void sortComponents();
public:
    constexpr TriFuzzyNum(real_t low, real_t mod, real_t up) {
        if (up < low) std::swap(low, up);
        if (mod < low) std::swap(low, mod);
        if (up < mod) std::swap(mod, up);
        l = low;
        m = mod;
        u = up;
    }
    constexpr TriFuzzyNum(const TriFuzzyNum &other) = default;
    constexpr TriFuzzyNum(TriFuzzyNum &&other) = default;

    constexpr real_t lower_value() const { return l; }
    constexpr real_t modal_value() const { return m; }
    constexpr real_t upper_value() const { return u; }

    TriFuzzyNum &operator=(const TriFuzzyNum &other) = default;
    TriFuzzyNum &operator=(TriFuzzyNum &&other) = default;

    TriFuzzyNum& operator+=(const TriFuzzyNum &rhs);
    TriFuzzyNum& operator-=(const TriFuzzyNum &rhs);
    TriFuzzyNum& operator*=(const TriFuzzyNum &rhs);

    const TriFuzzyNum operator+(const TriFuzzyNum &rhs) const;
    const TriFuzzyNum operator-(const TriFuzzyNum &rhs) const;
    const TriFuzzyNum operator*(const TriFuzzyNum &rhs) const;

    const std::partial_ordering operator<=>(const TriFuzzyNum &rhs) const;

    constexpr bool operator==(const TriFuzzyNum &rhs) const {
        return (l == rhs.l) && (m == rhs.m) && (u == rhs.u);
    }

    constexpr bool operator!=(const TriFuzzyNum &rhs) const {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const TriFuzzyNum& n);
};

class TriFuzzyNumSet {
    std::multiset<TriFuzzyNum> s;

public:
    TriFuzzyNumSet() = default;
    TriFuzzyNumSet(std::initializer_list<TriFuzzyNum> l) : s(l) {};
    ~TriFuzzyNumSet();
    TriFuzzyNumSet(const TriFuzzyNumSet &other) = default;
    TriFuzzyNumSet &operator=(const TriFuzzyNumSet &other) = default;
    TriFuzzyNumSet(TriFuzzyNumSet &&other) = default;
    TriFuzzyNumSet &operator=(TriFuzzyNumSet &&other) = default;
    void insert(const TriFuzzyNum &n);
    void insert(TriFuzzyNum &&n);
    void remove(const TriFuzzyNum &n);
    void remove(TriFuzzyNum &&n);
    TriFuzzyNum arithmetic_mean();
};

consteval TriFuzzyNum crisp_number(real_t v) {
    return TriFuzzyNum(v, v, v);
}

constinit const TriFuzzyNum crisp_zero = crisp_number(0);

#endif //FUZZY_H
