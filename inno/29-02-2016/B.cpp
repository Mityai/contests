#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);

    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int ans = 0;
    for (int i = 0, cur = 0; i < n; i++) {
        if (a[i] > 0) cur++;
        else cur = 0;
        ans = max(ans, cur);
    }

    printf("%d\n", ans);
}
