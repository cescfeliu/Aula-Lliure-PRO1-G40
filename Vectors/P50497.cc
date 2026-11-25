// És un palíndrom?
// https://jutge.org/problems/P50497_ca
// P50497_ca:std:no_main:G++17

#include <iostream>
#include <string>
using namespace std;

bool es_palindrom(const string& s) {
    const int sz = s.size();
    for (int i = 0; i < sz/2; i++) {
        if (s[i] != s[sz - 1 - i]) {
            return false;
        }
    }
    return true;
}
