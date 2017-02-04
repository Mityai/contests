#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }

        int ans = 0;
        int free = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] != 0) {
                int j = i;
                while (j + 1 < n && a[i] == a[j + 1]) j++;
                int em = j + 1;
                for (int k = j; k >= i; k--) {
                    if (a[free] == 0) {
                        a[free] = a[k];
                        a[k] = 0;
                        free++;
                        ans++;
                        em = k;
                    }
                }
                if (a[free] != 0) free = em;
                i = j;
            } else if (a[free] != 0) free = i;
        }
        printf("%d\n", ans);
    }
}
