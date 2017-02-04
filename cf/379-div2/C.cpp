#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

struct M {
    ll t, c;
};

struct Q {
    ll k, c;
};

bool cmpM(M& a, M& b) {
    return a.c < b.c;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    ll n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);

    ll x, s;
    scanf("%lld%lld", &x, &s);

    vector<M> a(m);
    for (int i = 0; i < m; i++) {
        scanf("%lld", &a[i].t);
        a[i].t = min(a[i].t, x);
    }
    for (int i = 0; i < m; i++) {
        scanf("%lld", &a[i].c);
    }

    vector<Q> b(k);
    for (int i = 0; i < k; i++) {
        scanf("%lld", &b[i].k);
        b[i].k = min(b[i].k, n);
    }
    for (int i = 0; i < k; i++) {
        scanf("%lld", &b[i].c);
    }

    sort(a.begin(), a.end(), cmpM);

    for (int i = 1; i < m; i++) {
        a[i].t = min(a[i].t, a[i - 1].t);
    }

    for (int i = 1; i < k; i++) {
        b[i].k = max(b[i].k, b[i - 1].k);
    }

    ll ans = x * n;
    for (int i = 0; i < m; i++) {
        if (a[i].c <= s) {
            ans = min(ans, n * a[i].t);
        }
    }
    for (int i = 0; i < k; i++) {
        if (b[i].c <= s) {
            ans = min(ans, (n - b[i].k) * x);
        }
    }

    int mi = 0, qi = k - 1;
    while (mi < m && qi >= 0) {
        while (mi + 1 < m && a[mi + 1].c + b[qi].c <= s) {
            mi++;
        }
        if (a[mi].c + b[qi].c <= s) {
            ans = min(ans, (n - b[qi].k) * a[mi].t);
        }
        qi--;
    }

    printf("%lld\n", ans);
}
