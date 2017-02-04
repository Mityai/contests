#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const double eps = 1e-8;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        double pmin[n], pmax[n];
        for (int i = 0; i < n; i++) {
            scanf("%lf", &pmax[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%lf", &pmin[i]);
        }

        double pa[n], pb[n];

        double sum = 0;
        for (int i = 0; i < n; i++) {
            double g = pmin[i] + pmax[i];
            double f = pmax[i] - sum;

            double d = g * g - 4 * f;

            if (fabs(d) < eps) {
                double x = g / 2;
                pa[i] = pb[i] = x;
            } else {
                double x1 = (g - sqrt(d)) / 2;
                double x2 = (g + sqrt(d)) / 2;
                pa[i] = x1;
                pb[i] = x2;
            }

            for (int j = 0; j < i; j++) {
                sum += pa[i] * pb[j];
                sum += pb[i] * pa[j];
            }
            sum += pa[i] * pb[i];
        }

        for (int i = 0; i < n; i++) {
            printf("%.8lf ", pa[i]);
        }
        puts("");
        for (int i = 0; i < n; i++) {
            printf("%.8lf ", pb[i]);
        }
        puts("");
    }
}
