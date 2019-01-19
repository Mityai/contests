#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mult(ll a, ll b, ll p) {
    return (a * b) % p;
}

ll binpow(ll a, ll n, ll p) {
    if (n == 0) return 1 % p;
    if (n == 1) return a % p;
    ll b = binpow(a, n / 2, p);
    b = mult(b, b, p);
    if (n & 1) b = mult(b, a, p);
    return b;
}

void solve(ll a, ll b, ll p, ll x) {
    ll arev = binpow(a, p - 2, p);
    ll pw_a = 1;
    ll max_k = x / (p - 1);
    ll sum_k = 0;
    for (ll m = 1; m <= p - 2; ++m) {
        pw_a = mult(pw_a, arev, p);
        ll right_side = (m - mult(pw_a, b, p)) % p;
        if (right_side < 0) right_side += p;
        sum_k += max_k / (p - 1) + (max_k % (p - 1) <= right_side);
    }
    printf("%lld\n", sum_k);
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    ll a, b, p, x;
    while (scanf("%lld%lld%lld%lld", &a, &b, &p, &x) == 4) {
        solve(a, b, p, x);
    }
}
