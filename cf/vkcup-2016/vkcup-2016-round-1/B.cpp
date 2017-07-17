#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n, h, d;
    while (scanf("%d%d%d", &n, &d, &h) == 3) {
        //puts("---------");
        if (d < h || d > 2 * h) {
            puts("-1");
            continue;
        }

        //vector< vector<int> > g(n);
        vector< pair<int, int> > ans;
        int v = 0;
        for (int i = 0; i < h; i++, v++) {
            ans.push_back({v, v + 1});
            //g[v].push_back(v + 1);
        }
        v++;

        if (d > h) {
            for (int i = 0, prev = 0; i < d - h; i++, v++) {
                ans.push_back({prev, v});
                prev = v;
            }
            for (; v < n; v++) {
                ans.push_back({0, v});
            }
        } else {
            if (d != 1 && h != 1) {
                for (; v < n; v++) {
                    ans.push_back({1, v});
                }
            }
        }

        if (v > n || ans.size() != n - 1) {
            puts("-1");
            continue;
        }

        assert(v == n);

        for (int i = 0; i < n - 1; i++) {
            printf("%d %d\n", ans[i].fi + 1, ans[i].se + 1);
        }
    }
}
