#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n;
        scanf("%d", &n);

        vector<vector<int>> a(2, vector<int>(n / 2 + n % 2));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i % 2][i / 2]);
        }
        sort(a[0].begin(), a[0].begin() + n / 2 + n % 2);
        sort(a[1].begin(), a[1].begin() + n / 2);

        printf("Case #%d: ", test);

        vector<int> b(n);
        for (int i = 0; i < n / 2; ++i) {
            b[i + i] = a[0][i];
            b[i + i + 1] = a[1][i];
        }
        if (n & 1) b.back() = a[0][n / 2];

        bool ok = true;
        for (int i = 0; i + 1 < n; ++i) {
            if (b[i] > b[i + 1]) {
                printf("%d\n", i);
                ok = false;
                break;
            }
        }
        if (ok) {
            puts("OK");
        }
    }
}
