#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int ans = 6;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int diff = 0;
                for (int k = 0; k < 6; k++) {
                    diff += (a[i][k] != a[j][k]);
                }
                ans = min(ans, (diff + 1) / 2 - 1);
            }
        }

        printf("%d\n", ans);
    }
}
