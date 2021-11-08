#include "fuzzy.h"

using namespace std;

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
        sum_l = a.lower_value();
        sum_m = a.modal_value();
        sum_u = a.upper_value();
    }

    return TriFuzzyNum(sum_l / size, sum_m / size, sum_u / size);
}
