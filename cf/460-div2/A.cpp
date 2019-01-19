#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    // freopen("A.in", "r", stdin);
    // freopem("A.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    double ans = 1e15;
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        ans = min(ans, double(a) / b * m);
    }

    printf("%.10lf\n", ans);
}
