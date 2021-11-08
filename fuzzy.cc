#include "fuzzy.h"

using namespace std;

//TriFuzzyNumSet::TriFuzzyNumSet(const TriFuzzyNumSet &other) {
//
//}
//
//TriFuzzyNumSet &TriFuzzyNumSet::operator=(const TriFuzzyNumSet &other) {
//    return ;
//}
//
//TriFuzzyNumSet::TriFuzzyNumSet(const TriFuzzyNumSet &&other) {
//
//}
//
//TriFuzzyNumSet &TriFuzzyNumSet::operator=(TriFuzzyNumSet &&other) {
//    return ;
//}
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
    real_t l = 0, m = 0, u = 0;
    for (auto n : s) {
//        sum += n;
    }
    return TriFuzzyNum(l, m, u);
}
