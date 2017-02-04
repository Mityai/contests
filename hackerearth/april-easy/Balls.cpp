#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);

    ll a[n];
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    sort(a, a + n);
    ll ans = 0;

    for (ll i = 1, x = 1; i <= n; i++, x++) {
        while (x * x < a[i - 1]) {
            ans += x * x;
            x++;
        }
        ans += x * x - a[i - 1];
    }

    printf("%lld\n", ans);
}
