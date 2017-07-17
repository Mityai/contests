#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    --m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    
    int ri = 1e5;
    for (int i = m + 1; i < n; ++i) {
        if (a[i] <= k && a[i] != 0) {
            ri = i;
            break;
        }
    }
    int le = -1e5;
    for (int i = m - 1; i >= 0; --i) {
        if (a[i] <= k && a[i] != 0) {
            le = i;
            break;
        }
    }

    int ans = min(ri - m, m - le);
    printf("%d\n", ans * 10);
}
