#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        vector<ll> v(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
        }

        vector<ll> t(n);
        vector<ll> suff_t(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &t[i]);
            suff_t[i] = t[i];
            if (i > 0) {
                suff_t[i] += suff_t[i - 1];
            }
        }

        vector<ll> melt(n);
        vector<ll> melt_cnt(n);
        for (int i = 0; i < n; ++i) {
            int lb = i - 1, rb = n;
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                ll sum_t = suff_t[mb];
                if (i > 0) sum_t -= suff_t[i - 1];

                if (v[i] >= sum_t) {
                    lb = mb;
                } else {
                    rb = mb;
                }
            }
            if (rb == n) continue;
            ll sum_t = 0;
            if (rb != 0) {
                sum_t = suff_t[rb - 1];
            }
            if (i != 0) sum_t -= suff_t[i - 1];
            melt[rb] += v[i] - sum_t;
            ++melt_cnt[rb];
        }

        ll cnt = 0;
        for (int i = 0; i < n; ++i) {
            ++cnt;
            ll sum = melt[i];
            cnt -= melt_cnt[i];
            sum += cnt * 1ll * t[i];
            printf("%lld ", sum);
        }
        putchar('\n');
    }
}
