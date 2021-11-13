#include "fuzzy.h"
#include <cmath>

using namespace std;

TriFuzzyNum& TriFuzzyNum::operator+=(const TriFuzzyNum &rhs) {
    l += rhs.l;
    m += rhs.m;
    u += rhs.u;
    return *this;
}

TriFuzzyNum& TriFuzzyNum::operator-=(const TriFuzzyNum &rhs) {
    l -= rhs.u;
    m -= rhs.m;
    u -= rhs.l;
    return *this;
}

TriFuzzyNum& TriFuzzyNum::operator*=(const TriFuzzyNum &rhs) {
    l *= rhs.l;
    m *= rhs.m;
    u *= rhs.u;
    if (u < l) std::swap(l, u);
    if (m < l) std::swap(l, m);
    if (u < m) std::swap(m, u);
    return *this;
}

const TriFuzzyNum TriFuzzyNum::operator+(const TriFuzzyNum &rhs) const {
    return TriFuzzyNum(*this) += rhs;
}

const TriFuzzyNum TriFuzzyNum::operator-(const TriFuzzyNum &rhs) const {
    return TriFuzzyNum(*this) -= rhs;
}

const TriFuzzyNum TriFuzzyNum::operator*(const TriFuzzyNum &rhs) const {
    return TriFuzzyNum(*this) *= rhs;
}

const tuple<real_t, real_t, real_t> TriFuzzyNum::getRank() const {
    real_t z = (u - l) + sqrt(1 + (u - m) * (u - m)) +
            sqrt(1 + (m - l) * (m - l));
    real_t y = (u - l) / z;
    real_t x = ((u - l) * m + sqrt(1 + (u - m) * (u - m)) * l +
            sqrt(1 + (m - l) * (m - l)) * u) / z;
    return make_tuple((x-y)/2, 1-y, m);
}

const partial_ordering TriFuzzyNum::operator<=>(const TriFuzzyNum &rhs) const {
    auto rank1 = getRank();
    auto rank2 = rhs.getRank();

    auto comp1 = get<0>(rank1) <=> get<0>(rank2);
    if (comp1 != 0)
        return comp1;

    auto comp2 = get<1>(rank1) <=> get<1>(rank2);
    if (comp2 != 0)
        return comp2;
    else
        return get<2>(rank1) <=> get<2>(rank2);
}

ostream& operator<<(std::ostream& os, const TriFuzzyNum& n) {
    return os << "(" << n.l << ", " << n.m << ", " << n.u << ")";
}

TriFuzzyNumSet::~TriFuzzyNumSet() {
    s.clear();
}

void TriFuzzyNumSet::insert(const TriFuzzyNum &n) {
    s.insert(n);
}

void TriFuzzyNumSet::insert(TriFuzzyNum &&n) {
    s.insert(n);
}

void TriFuzzyNumSet::remove(const TriFuzzyNum &n) {
    s.erase(n);
}

void TriFuzzyNumSet::remove(TriFuzzyNum &&n) {
    s.erase(n);
}

TriFuzzyNum TriFuzzyNumSet::arithmetic_mean() {
    if (s.empty()) {
        throw length_error("TriFuzzyNumSet::arithmetic_mean"
                           " - the set is empty.");
    }

    real_t sum_l = 0, sum_m = 0, sum_u = 0, size = (double) s.size();

    for (auto a : s) {
        sum_l += a.lower_value();
        sum_m += a.modal_value();
        sum_u += a.upper_value();
    }

    return TriFuzzyNum(sum_l / size, sum_m / size, sum_u / size);
}
