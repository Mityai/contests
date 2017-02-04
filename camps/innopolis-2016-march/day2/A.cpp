#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    freopen("set.dat", "r", stdin);
    freopen("set.sol", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1) {
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }

        sort(a, a + n);

        ll sum = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] < sum && i >= 2) ans = i + 1;
            sum += a[i];
        }

        printf("%d\n", ans);
    }
}
