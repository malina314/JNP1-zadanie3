#ifndef FUZZY_H
#define FUZZY_H

#include <set>
#include <tuple>

using real_t = double;

class TriFuzzyNum {
    real_t l;
    real_t m;
    real_t u;
    
    const std::tuple<real_t, real_t, real_t> getRank() const;
public:
    constexpr TriFuzzyNum(real_t low, real_t mod, real_t up):
        l(low), m(mod), u(up) {}

    constexpr TriFuzzyNum(const TriFuzzyNum &other) = default;
    constexpr TriFuzzyNum(TriFuzzyNum &&other) = default;

    constexpr const real_t lower_value() { return l; }
    constexpr const real_t modal_value() { return m; }
    constexpr const real_t upper_value() { return u; }

    TriFuzzyNum &operator=(const TriFuzzyNum &other) = default;
    TriFuzzyNum &operator=(TriFuzzyNum &&other) = default;
    
    TriFuzzyNum& operator+=(const TriFuzzyNum &rhs);
    TriFuzzyNum& operator-=(const TriFuzzyNum &rhs);
    TriFuzzyNum& operator*=(const TriFuzzyNum &rhs);
    
    const TriFuzzyNum operator+(const TriFuzzyNum &rhs) const;
    const TriFuzzyNum operator-(const TriFuzzyNum &rhs) const;
    const TriFuzzyNum operator*(const TriFuzzyNum &rhs) const;
    
    const std::partial_ordering operator<=>(const TriFuzzyNum &rhs) const;
    
    constexpr const bool operator==(const TriFuzzyNum &rhs) const {
        return (l == rhs.l) && (m == rhs.m) && (u == rhs.u);
    }

    constexpr const bool operator!=(const TriFuzzyNum &rhs) const {
        return !(*this == rhs);
    }
};

class TriFuzzyNumSet {
    std::multiset<TriFuzzyNum> s;

public:
    TriFuzzyNumSet() = default;
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

#endif //FUZZY_H
