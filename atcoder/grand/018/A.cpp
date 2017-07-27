#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    int g = 0;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        mx = max(mx, x);
        g = __gcd(g, x);
    }

    if (k % g == 0 && k <= mx) {
        puts("POSSIBLE");
    } else {
        puts("IMPOSSIBLE");
    }
}
