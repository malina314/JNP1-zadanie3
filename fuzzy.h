// autorzy: Mateusz Malinowski (mm429561), Maciej Mućka (mm429572)

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

    /**
     * Oblicz i zwróć rangę liczby rozmytej.
     *
     * Ranga jest krotką używaną do porównywania obiektów. Poszczególne rangi
     * należy porównywać leksykograficznie.
     */
    const std::tuple<real_t, real_t, real_t> getRank() const;

    /**
     * Sortuj elementy obiektu TriFuzzyNum.
     *
     * Służy do przywracania porządku po operacjach, które mogą go zaburzyć.
     */
    constexpr void sortComponents() {
        if (u < l) std::swap(l, u);
        if (m < l) std::swap(l, m);
        if (u < m) std::swap(m, u);
    };

public:
    constexpr TriFuzzyNum(real_t low, real_t mod, real_t up) : l(low), m(mod), u(up) {
        sortComponents();
    }

    constexpr TriFuzzyNum(const TriFuzzyNum& other) = default;
    constexpr TriFuzzyNum(TriFuzzyNum&& other) = default;

    constexpr real_t lower_value() const { return l; }
    constexpr real_t modal_value() const { return m; }
    constexpr real_t upper_value() const { return u; }

    TriFuzzyNum& operator=(const TriFuzzyNum& other) = default;
    TriFuzzyNum& operator=(TriFuzzyNum&& other) = default;

    TriFuzzyNum& operator+=(const TriFuzzyNum& rhs);
    TriFuzzyNum& operator-=(const TriFuzzyNum& rhs);
    TriFuzzyNum& operator*=(const TriFuzzyNum& rhs);

    const TriFuzzyNum operator+(const TriFuzzyNum& rhs) const;
    const TriFuzzyNum operator-(const TriFuzzyNum& rhs) const;
    const TriFuzzyNum operator*(const TriFuzzyNum& rhs) const;

    const std::partial_ordering operator<=>(const TriFuzzyNum& rhs) const;

    constexpr bool operator==(const TriFuzzyNum& rhs) const {
        return (l == rhs.l) && (m == rhs.m) && (u == rhs.u);
    }

    constexpr bool operator!=(const TriFuzzyNum& rhs) const {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const TriFuzzyNum& n);
};

class TriFuzzyNumSet {
    std::multiset<TriFuzzyNum> s;

public:
    TriFuzzyNumSet() = default;
    TriFuzzyNumSet(std::initializer_list<TriFuzzyNum> l) : s(l) {};
    TriFuzzyNumSet(const TriFuzzyNumSet& other) = default;
    TriFuzzyNumSet& operator=(const TriFuzzyNumSet& other) = default;
    TriFuzzyNumSet(TriFuzzyNumSet&& other) = default;
    TriFuzzyNumSet& operator=(TriFuzzyNumSet&& other) = default;

    /**
     * Wstaw daną liczbę do zbioru.
     */
    void insert(const TriFuzzyNum& n);
    void insert(TriFuzzyNum&& n);

    /**
     * Usuń daną liczbę ze zbioru.
     *
     * Usuwa wszystkie wystąpienia danej liczby. Nie można swobodnie
     * zamieniać ze sobą operacji insert i remove.
     */
    void remove(const TriFuzzyNum& n);

    /**
     * Oblicz i zwróć średnią arytmetyczną elementów zbioru.
     */
    const TriFuzzyNum arithmetic_mean() const;
};

consteval static TriFuzzyNum crisp_number(real_t v) {
    return TriFuzzyNum(v, v, v);
}

constinit inline const TriFuzzyNum crisp_zero = crisp_number(0);

#endif //FUZZY_H
