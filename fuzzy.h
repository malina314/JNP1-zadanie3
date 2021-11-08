#ifndef FUZZY_H
#define FUZZY_H

#include <set>

using real_t = double;

class TriFuzzyNum {

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
