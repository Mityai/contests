#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    int mn = a[0];
    for (int i = 0; i < n; ++i) {
        mn = min(mn, a[i]);
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if ((a[i] - mn) % k != 0) {
            ans = -1;
        } else if (ans != -1) {
            ans += (a[i] - mn) / k;
        }
    }

    printf("%lld\n", ans);
}
