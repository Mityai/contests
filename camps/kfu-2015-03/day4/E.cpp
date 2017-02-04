#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        sort(a, a + n);

        ll ans = 1;
        for (int i = 0; i < n; i++) {
            ll cnt = max(0, a[i] - i);
            ans = (ans * cnt) % MOD;
        }

        printf("%lld\n", ans);
    }
}
