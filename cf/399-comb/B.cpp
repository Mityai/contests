#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

unordered_map<ll, ll> cnt;
unordered_map<ll, ll> sz;

ll calcsz(ll v) {
    if (v <= 1) {
        return sz[v] = 1;
    }
    return sz[v] = 2ll * calcsz(v / 2) + 1;
}

ll go(ll v, ll L, ll R, ll b) {
    if (b <= L) return 0;
    if (v <= 1) {
        return cnt[v] = v;
    }
    if (R <= b && cnt.find(v) != cnt.end()) {
        return cnt[v];
    }
    ll ret = go(v / 2, L, L + sz[v / 2], b);
    ret += go(v / 2, L + sz[v / 2] + 1, L + sz[v], b);
    if (L + sz[v / 2] + 1 <= b) {
        ret += v % 2;
    }
    return cnt[v] = ret;
}

ll solve(ll x, ll b) {
    cnt.clear();
    return go(x, 0, sz[x], b);
}

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    ll n, l, r;
    scanf("%lld%lld%lld", &n, &l, &r);
    calcsz(n);

    printf("%lld\n", solve(n, r) - solve(n, l - 1));
}
