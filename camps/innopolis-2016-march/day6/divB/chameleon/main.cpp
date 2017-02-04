#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("01", "r", stdin);
    freopen("01.out", "w", stdout);
#else
    freopen("chameleon.in", "r", stdin);
    freopen("chameleon.out", "w", stdout);
#endif

    int n;
    cin >> n;

    int a[n][n];
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = (s[j] == 'B');
        }
    }

    int c[n][n];
    memset(c, 0, sizeof c);

    c[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < n; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    putchar('r');
                } else {
                    putchar('R');
                }
            } else {
                if (j % 2 == 0) {
                    putchar('l');
                } else {
                    putchar('L');
                }
            }
        }
        if (i + 1 < n) {
            putchar('D');
        }
    }
}
