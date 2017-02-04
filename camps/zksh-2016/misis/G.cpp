#include <bits/stdc++.h>
using namespace std;

const int N = 1123;

int a[N][N];

int main() {
#if __APPLE__
    freopen("G.in", "r", stdin);
    freopen("G.out", "w", stdout);
#endif

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x1, y1, x2, y2, val;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &val);

        a[x1][y1] += val;
        a[x1][y2 + 1] -= val;
        a[x2 + 1][y1] -= val;
        a[x2 + 1][y2 + 1] += val;
    }

    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            a[i][j] += x;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", a[i][j]);
        }
        puts("");
    }
}
