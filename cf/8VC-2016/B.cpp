#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
    ll s, x;
    while (cin >> s >> x) {
        ll d = s - x;

        if (d < 0) {
            cout << 0 << endl;
        } else {
            cout << (1LL << __builtin_popcountll(x)) - (s == x ? 2 : 0) << endl;
        }

        int cnt = 0;
        for (ll a = 1; a < s; a++) {
            ll b = s - a;
            if ((a ^ b) == x) {
                cout << a << ' ' << b << endl;
                cnt++;
            }
        }
        cout << cnt << endl;
    }
}
