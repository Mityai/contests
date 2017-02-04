#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("F.in", "r", stdin);
    freopen("F.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<double> V(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &V[i]);
    }

    vector<double> w(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &w[i]);
    }

    double T = 0;
    double curV = 0;
    for (int i = n - 1; i >= 0; i--) {
        curV += V[i];
        V[i] = max(0.0, curV - w[i] * T);
        T += V[i] / w[i];
    }

    printf("%.10lf\n", T);
}
