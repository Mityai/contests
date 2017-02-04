#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n;
    cin >> n;

    ll lb = 0, rb = 1;
    while (rb * rb * rb < n) ++rb;

    while (lb + 1 < rb) {
        ll mb = (lb + rb) / 2;
        if (mb * mb * mb < n) lb = mb;
        else rb = mb;
    }
    cout << rb << '\n';
}
