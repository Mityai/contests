#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e5;

int n, m;
int a[2][N];
bool used[2][N];
vector<int> g[N], h[N];

bool go(int v, int s, int t) {
    used[t][v] = true;
    bool ok = true;
    for (int u : g[v]) a[t][u] ^= s;
    for (int u : g[v]) {
        for (int f : h[u]) {
            if (f != v) {
                if (!used[t][f]) {
                    if (a[t][u] == 1) {
                        ok &= go(f, 0, t);
                    } else {
                        ok &= go(f, 1, t);
                    }
                } else {
                    if (a[t][u] == 0) {
                        ok = false;
                        break;
                    }
                }
            }
        }
        if (!ok) break;
    }
    return ok;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[0][i]);
        a[1][i] = a[0][i];
    }

    for (int i = 0; i < m; ++i) {
        int xi;
        scanf("%d", &xi);

        for (int j = 0; j < xi; ++j) {
            int p;
            scanf("%d", &p);
            --p;
            g[i].push_back(p);
            h[p].push_back(i);
        }
    }

    bool ok = true;
    for (int i = 0; i < m; ++i) {
        if (!used[0][i]) {
            if (!go(i, 0, 0)) {
                if (!go(i, 1, 1)) {
                    ok = false;
                    break;
                }
            }
        }
    }

    if (ok) {
        puts("YES");
    } else {
        puts("NO");
    }
}
