#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n, U;
    while (scanf("%d%d", &n, &U) == 2) {
        vector<int> E(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &E[i]);
        }

        double best = 0;
        bool was = false;

        for (int i = 0, k = 0; i < n; ++i) {
            while (k + 1 < n && E[k + 1] - E[i] <= U) {
                ++k;
            }
            if (i + 1 < k) {
                int j = i + 1;
                best = max(best, static_cast<double>(E[k] - E[j]) / (E[k] - E[i]));
                was = true;
            }
        }

        if (!was) {
            puts("-1");
        } else {
            printf("%.10lf\n", best);
        }
    }
}
