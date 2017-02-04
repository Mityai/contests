#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll n;
    cin >> n;

    int ans = 0;
    for (ll y = 1; y * y * y <= n; y++) {
        ll rest = n - y * y * y;
        ll x = sqrt(rest);

        if (x > 0 && x * x + y * y * y == n) {
            ans++;
        }
    }
    printf("%d\n", ans);
}
