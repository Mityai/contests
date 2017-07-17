#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int ii = 0; ii < t; ++ii) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);

        vector<vector<int>> a(n + 2, vector<int>(m + 2));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[i][j]);
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (a[i][j] == 1) {
                    a[i][j] = (i + j) % k + 1;
                }
            }
        }

        bool ok = true;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                vector<char> has(k, false);
                for (int k = i + 1; a[k][j] != 0; ++k) {
                    if (has[a[k][j] - 1] == true) {
                        ok = false;
                        break;
                    } else {
                        has[a[k][j] - 1] = true;
                    }
                }
                has.assign(k, false);
                for (int k = j + 1; a[i][k] != 0; ++k) {
                    if (has[a[i][k] - 1] == true) {
                        ok = false;
                        break;
                    } else {
                        has[a[i][k] - 1] = true;
                    }
                }
                if (!ok) break;
            }
            if (!ok) break;
        }

        if (ok) {
            puts("YES");
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    printf("%d ", a[i][j]);
                }
                puts("");
            }
        } else {
            puts("NO");
        }
    }
}
