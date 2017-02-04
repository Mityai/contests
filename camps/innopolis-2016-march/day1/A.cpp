#include <bits/stdc++.h>
#define se second
using namespace std;

void solve(int n) {
    int a[n], p[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        --a[i];
        p[a[i]] = i;
    }

    int f[n];
    memset(f, 0, sizeof f);
    for (int i = 0; i < n; i++) {
        int b;
        scanf("%d", &b);
        --b;
        int st = (i - p[b] + n) % n;
        f[st]++;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, f[i]);
    }
    printf("%d\n", ans);
}

void solveslow(int n) {
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }

    int b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", b + i);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < n; j++) {
            int k = (i + j) % n;
            if (a[j] == b[k]) cur++;
        }
        ans = max(ans, cur);
    }

    printf("%d\n", ans);
}

int main() {
    freopen("calendar.dat", "r", stdin);
    freopen("calendar.sol", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1) {
        solve(n);
    }
}
