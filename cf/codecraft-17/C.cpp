#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int P = 1e6 + 103;
const int N = 1e6;

ll fact[N + 1];
ll pPow[N + 1];

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    fact[0] = 1;
    for (ll i = 1; i <= N; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    pPow[0] = 1;
    for (int i = 1; i <= N; ++i) {
        pPow[i] = (pPow[i - 1] * P) % MOD;
    }

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {

    vector<ll> hs(m + 1, 1);
    vector<int> last(m + 1);
    unordered_set<int> used;
    for (int i = 0; i < n; i++) {
        int g;
        scanf("%d", &g);

        map<int, int> cnt;
        for (int j = 0; j < g; ++j) {
            int x;
            scanf("%d", &x);
            ++cnt[x];
            used.insert(x);
        }

        for (auto& p : cnt) {
            int x = p.fi;
            int y = p.se;
            hs[x] = (hs[x] * pPow[i - last[x]] + y) % MOD;
            last[x] = i;
        }
    }
    
    unordered_map<int, int> cnt;
    for (int i = 1; i <= m; ++i) {
        if (used.find(i) != used.end()) {
            ++cnt[hs[i]];
        }
    }

    ll ans = fact[m - used.size()];
    for (auto& p : cnt) {
        ans = (ans * fact[p.se]) % MOD;
    }

    printf("%lld\n", ans);
}
}
