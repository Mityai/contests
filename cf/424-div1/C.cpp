#include <bits/stdc++.h>
#define div asdjkld
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e15;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n; ll k;
    while (scanf("%d%lld", &n, &k) == 2) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            k += a[i];
        }

        vector<int> d;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j * j <= a[i]; ++j) {
                d.push_back(j);
                d.push_back((a[i] + j - 1) / j);
            }
        }
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());

        ll ans = 0;
        for (int i = 0; i < d.size(); ++i) {
            int l = d[i];
            ll cur = 0;
            for (int j = 0; j < n; ++j) {
                cur += (a[j] + l - 1) / l;
            }
            ll x = k / cur;
            if (x >= l && ans < x) {
                ans = x;
            }
        }
        printf("%lld\n", ans);
    }
}
