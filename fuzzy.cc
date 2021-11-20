// autorzy: Mateusz Malinowski (mm429561), Maciej Mućka (mm429572)

#include "fuzzy.h"
#include <cmath>

TriFuzzyNum& TriFuzzyNum::operator+=(const TriFuzzyNum& rhs) {
    l += rhs.l;
    m += rhs.m;
    u += rhs.u;
    return *this;
}

TriFuzzyNum& TriFuzzyNum::operator-=(const TriFuzzyNum& rhs) {
    l -= rhs.u;
    m -= rhs.m;
    u -= rhs.l;
    return *this;
}

TriFuzzyNum& TriFuzzyNum::operator*=(const TriFuzzyNum& rhs) {
    l *= rhs.l;
    m *= rhs.m;
    u *= rhs.u;
    sortComponents();
    return *this;
}

const TriFuzzyNum TriFuzzyNum::operator+(const TriFuzzyNum& rhs) const {
    return TriFuzzyNum(*this) += rhs;
}

const TriFuzzyNum TriFuzzyNum::operator-(const TriFuzzyNum& rhs) const {
    return TriFuzzyNum(*this) -= rhs;
}

const TriFuzzyNum TriFuzzyNum::operator*(const TriFuzzyNum& rhs) const {
    return TriFuzzyNum(*this) *= rhs;
}

const std::tuple<real_t, real_t, real_t> TriFuzzyNum::getRank() const {
    real_t z = (u - l) + sqrt(1 + (u - m) * (u - m)) +
            sqrt(1 + (m - l) * (m - l));
    real_t y = (u - l) / z;
    real_t x = ((u - l) * m + sqrt(1 + (u - m) * (u - m)) * l +
            sqrt(1 + (m - l) * (m - l)) * u) / z;

    return std::make_tuple(x - y / 2, 1 - y, m);
}

const std::partial_ordering TriFuzzyNum::operator<=>(const TriFuzzyNum& rhs) const {
    // Domyślny operator<=> porównuje krotki leksykograficznie.
    return getRank() <=> rhs.getRank();
}

std::ostream& operator<<(std::ostream& os, const TriFuzzyNum& n) {
    return os << "(" << n.l << ", " << n.m << ", " << n.u << ")";
}

void TriFuzzyNumSet::insert(const TriFuzzyNum& n) { s.insert(n); }

void TriFuzzyNumSet::insert(TriFuzzyNum&& n) { s.insert(n); }

void TriFuzzyNumSet::remove(const TriFuzzyNum& n) { s.erase(n); }

const TriFuzzyNum TriFuzzyNumSet::arithmetic_mean() const {
    if (s.empty()) {
        throw std::length_error("TriFuzzyNumSet::arithmetic_mean"
                           " - the set is empty.");
    }

    real_t sum_l = 0, sum_m = 0, sum_u = 0,
        size = static_cast<real_t>(s.size());

    for (auto a : s) {
        sum_l += a.lower_value();
        sum_m += a.modal_value();
        sum_u += a.upper_value();
    }

    return TriFuzzyNum(sum_l / size, sum_m / size, sum_u / size);
}
