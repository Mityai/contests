#include <bits/stdc++.h>
using namespace std;

int main() {
    double x, d;
    while (scanf("%lf%lf", &x, &d) == 2) {
        int n;
        scanf("%d", &n);

        double t[n];
        for (int i = 0; i < n; i++) {
            scanf("%lf", &t[i]);
        }

        bool demi = (t[0] > x);
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (t[i] <= x - d) {
                demi = false;
            } else if (t[i] >= x + d) {
                demi = true;
            }
            if (t[i] <= x && demi) ans++;
            if (t[i] > x && !demi) ans++;
        }
        printf("%d\n", ans);
    }
}
