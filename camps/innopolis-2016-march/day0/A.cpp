#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    freopen("conquest.in", "r", stdin);
    freopen("conquest.out", "w", stdout);

    int n;
    scanf("%d", &n);

    ll ans = 0;
    for (int i = 0, sp; i < n - 1; i++) {
        int t;
        scanf("%d", &t);

        if (i == 0) sp = t;
        else sp = min(sp, t);
        ans += sp;
    }

    printf("%lld\n", ans);
}
