#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const ll MAX = 1e14;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    ll ans = 0;
    ll sum = 0;
    map<ll, int> cnt;
    cnt[0] = 1;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        for (ll step = 1; llabs(step) <= MAX;) {
            ans += cnt[sum - step];
            step *= k;
            if (step == 1) {
                break;
            }
        }
        ++cnt[sum];
    }

    printf("%lld\n", ans);
}
