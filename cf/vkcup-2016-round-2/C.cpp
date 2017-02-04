#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, q;
    while (scanf("%d%d", &n, &q) == 2) {
        int v = 0;

        vector<int> que;
        que.reserve(q);
        for (int i = 0; i < q; i++) {
            int x;
            scanf("%d", &x);

            if (x == 2) {
                if (que.empty()) {
                    que.push_back(v % 2);
                } else if (que.back() == v % 2) {
                    que.pop_back();
                } else {
                    que.push_back(v % 2);
                }
            } else {
                int d;
                scanf("%d", &d);
                v = (v - d + n) % n;
                if (v < 0) v += n;
            }
        }

        int ans[n];

        for (int i = 0; i < n; i++) ans[i] = i;

        if (!que.empty()) {
            int sz = que.size();
            if (que[0] == 0) {
                for (int i = 0; i < n; i++) {
                    if (i % 2 == 0) {
                        ans[(i + sz) % n] = i;
                    } else {
                        ans[((i - sz + n) % n + n) % n] = i;
                    }
                }
            } else {
                for (int i = 0; i < n; i++) {
                    if (i % 2 == 1) {
                        ans[(i + sz) % n] = i;
                    } else {
                        ans[((i - sz + n) % n + n) % n] = i;
                    }
                }
            }
        }

        printf("%d ", ans[v] + 1);
        for (int i = (v + 1) % n; i != v; i = (i + 1) % n) {
            printf("%d ", ans[i] + 1);
        }
        puts("");
    }
}
