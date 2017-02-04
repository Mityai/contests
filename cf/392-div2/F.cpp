#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll binpow(ll a, ll n) {
    if (n == 0) return 1;
    if (n == 1) return a;
    ll b = binpow(a, n / 2);
    b *= b;
    if (n & 1) b *= a;
    return b;
}

ll solve(ll n, ll l, ll r) {
    ll ret = 0;
    for (ll q = 1;; ++q) {
        ll qn = binpow(q, n - 1);
        if (qn > r) break;
        ll all = r / qn;
        ll mn = l / qn; if (l % qn == 0) --mn;
        for (ll p = q + 1;; ++p) {
            if (gcd(p, q) != 1) continue;
            ll pn = binpow(p, n - 1);
            ll lb = mn, rb = all + 1;
            while (lb + 1 < rb) {
                ll mb = (lb + rb) / 2;
                ll num = mb;

                if (num * pn <= r) {
                    lb = mb;
                } else {
                    rb = mb;
                }
            }
            if (lb - mn == 0) break;
            ret += lb - mn;
        }
    }
    return ret;
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    ll n, l, r;
    while (cin >> n >> l >> r) {
        if (n >= 30) {
            cout << 0 << endl;
            return 0;
        }
        if (n == 1) {
            cout << r - l + 1 << endl;
        } else if (n == 2) {
            ll len = r - l + 1;
            cout << len * (len - 1) << endl;
        } else {
            cout << 2 * solve(n, l, r) << endl;
        }
    }
}
