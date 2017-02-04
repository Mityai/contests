#include <bits/stdc++.h>
using namespace std;

void solve(int n) {
    int w[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", w + i);
    }

    int C;
    scanf("%d", &C);

    int f[n][C + 1];
    memset(f, -1, sizeof f);

    for (int i = 0; i < n; i++) {
        f[i][0] = i;
        if (w[i] <= C) {
            f[i][w[i]] = i;
        }
        if (i > 0) {
            for (int c = 0; c <= C; c++) {
                f[i][c] = max(f[i][c], f[i - 1][c]);
                if (c + w[i] <= C) {
                    f[i][c + w[i]] = max(f[i][c + w[i]], f[i - 1][c]);
                }
            }
        }
    }

    int q;
    scanf("%d", &q);

    for (int i = 0, k = 0; i < q; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int l = (a + k) % (n - b + 1) + 1;
        int r = l + b - 1;
        int t = (c + k) % (C + 1);
        --l, --r;
        if (f[r][t] >= l) putchar('Y'), k++;
        else putchar('N');
    }
    putchar('\n');
}

int main() {
    freopen("decisions.in", "r", stdin);
    freopen("decisions.out", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) return 0;
        solve(n);
    }
}
