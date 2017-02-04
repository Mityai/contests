#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int MOD = 1e9;

int main() {
    int n;
    scanf("%d", &n);

    map<int, int> a;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        for (ll p = 2; p * p <= x; p++) {
            while (x % p == 0) {
                a[p]++;
                x /= p;
            }
        }
        if (x != 1) a[x]++;
    }

    int m;
    scanf("%d", &m);

    map<int, int> b;
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);

        for (ll p = 2; p * p <= x; p++) {
            while (x % p == 0) {
                b[p]++;
                x /= p;
            }
        }
        if (x != 1) b[x]++;
    }

    ll ans = 1;
    bool f = false;
    for (auto x : a) {
        int pw = min(x.se, b[x.fi]);
        for (int i = 0; i < pw; i++) {
            ans = ans * x.fi;
            if (ans >= MOD) f = true;
            ans %= MOD;
        }
    }

    if (f) {
        printf("%09lld\n", ans);
    } else {
        printf("%lld\n", ans);
    }
}
