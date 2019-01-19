#include <bits/stdc++.h>
using namespace std;

const int N = 2000 + 1;

char a[N][N];
int l[N][N];
int u[N][N];

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < n; ++i) {
        scanf(" %s", a[i]);
    }

    for (int j = 0; j < m; ++j) {
        u[0][j] = (a[0][j] == '.');
    }
    for (int i = 0; i < n; ++i) {
        l[i][0] = (a[i][0] == '.');
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '.') {
                if (j - 1 >= 0) {
                    l[i][j] = 1 + l[i][j - 1];
                }
                if (i - 1 >= 0) {
                    u[i][j] = 1 + u[i - 1][j];
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans += (l[i][j] >= k) + (u[i][j] >= k);
        }
    }

    if (k == 1) ans /= 2;
    printf("%d\n", ans);
}
