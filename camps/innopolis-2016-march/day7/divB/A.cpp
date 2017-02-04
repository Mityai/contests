#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 1;

int main() {
    freopen("expedition.in", "r", stdin);
    freopen("expedition.out", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1) {
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            --a[i];
        }

        int next[N], to[N];
        memset(next, -1, sizeof next);
        memset(to, -1, sizeof to);

        int pos[N];
        memset(pos, -1, sizeof pos);
        for (int i = n - 1; i >= 0; i--) {
            next[i] = pos[a[i]];
            if (next[i] == -1) {
                to[i] = -1;
            } else if (next[next[i]] == -1 && next[i] != n - 1) {
                to[i] = next[i] - 1;
            } else {
                to[i] = next[i];
            }
            pos[a[i]] = i;
        }

        vector<int> ans;
        int v = 0;
        bool ok = false;
        while (true) {
            if (v == n - 1) {
                ok = true;
                break;
            }
            ans.push_back(v);
            int u = to[v];
            if (u == -1) break;
            int w = v;
            for (int i = v + 1; i <= u; i++) {
                if (to[i] > to[w]) {
                    w = i;
                }
            }
            if (to[w] == -1) break;
            if (v == w && to[w] == w) break;
            if (v == w) w = to[w];
            v = w;
        }

        if (ok) {
            printf("%d\n", (int)ans.size());
            for (int x : ans) {
                printf("%d ", x + 1);
            }
            puts("");
        } else {
            puts("0");
        }
    }
}
