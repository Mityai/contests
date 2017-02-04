#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        vector<int> a(n);
        vector<int> cnt(m + 1);
        for (int& x : a) {
            scanf("%d", &x);
            if (x <= m) {
                ++cnt[x];
            }
        }

        int ans = n / m;
        int changes = 0;
        for (int i = 1, j = 0; i <= m; ++i) {
            while (cnt[i] < ans) {
                if (a[j] > m || cnt[a[j]] > ans) {
                    if (a[j] <= m) {
                        --cnt[a[j]];
                    }
                    a[j] = i;
                    ++cnt[i];
                    ++changes;
                }
                ++j;
            }
        }

        printf("%d %d\n", ans, changes);
        for (int x : a) {
            printf("%d ", x);
        }
        puts("");
    }
}
