#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll p1, p2;
    cin >> p1 >> p2;

    if (p1 == 0 && p2 == 0) {
        cout << p1 << ' ' << p2 << endl;
    } else {
        for (int i = 3;; ++i) {
            ll t = p1 - p2;
            p1 = p2;
            p2 = t;
            if (p2 < 0) {
                cout << i << ' ' << p2 << endl;
                return 0;
            }
        }
    }
}
