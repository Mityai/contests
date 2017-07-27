#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> sum(n);
    vector<int> fi(m), se(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        ++sum[a], ++sum[b];
        fi[i] = a, se[i] = b;
    }
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += sum[fi[i]] + sum[se[i]];
    }
    printf("%lld\n", ans);
}
