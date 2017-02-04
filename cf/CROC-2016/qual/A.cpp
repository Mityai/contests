#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int n, a, b;
    while (scanf("%d%d%d", &n, &a, &b) == 3) {
        if (n > a * b) {
            puts("-1");
            return 0;
        }

        int d[a][b];
        memset(d, 0, sizeof d);
        for (int i = 0; i < n; i++) {
            d[i / b][i % b] = i + 1;
        }

        if (b % 2 == 0) {
            for (int i = 1; i < a; i += 2) {
                for (int j = 0; j < b; j += 2) {
                    swap(d[i][j], d[i][j + 1]);
                }
            }
        }

        /*
        printf("n = %d a = %d b = %d\n", n, a, b);
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                if (d[i][j] != 0) {
                    assert(i - 1 == -1 || d[i][j] % 2 != d[i - 1][j] % 2);
                    assert(i + 1 == a || d[i][j] % 2 != d[i + 1][j] % 2);
                    assert(j + 1 == b || d[i][j] % 2 != d[i][j + 1] % 2);
                    assert(j - 1 == -1 || d[i][j] % 2 != d[i][j - 1] % 2);
                }
            }
        }*/

        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                printf("%d ", d[i][j]);
            }
            puts("");
        }
    }
}
