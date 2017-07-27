#include <bits/stdc++.h>
using namespace std;

const int N = 150;

int m, n;
bool d[N][N], used[N];
int to[N], from[N];

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int u = 0; u < n; ++u) {
        if (!d[v][u] && (from[u] == -1 || dfs(from[u]))) {
            from[u] = v;
            to[v] = u;
            return true;
        }
    }
    return false;
}

void solve() {
    scanf("%d%d", &m, &n);

    memset(d, 0, sizeof d);
    for (int i = 0; i < m; ++i) {
        int x;
        while (scanf("%d", &x) == 1) {
            if (x == 0) break;
            --x;
            d[i][x] = true;
        }
    }

    vector<char> Lm(m), Rp(n);
    fill(from, from + n, -1);
    int match = 0;
    for (int i = 0; i < m; ++i) {
        memset(used, 0, m * sizeof(used[0]));
        if (dfs(i)) {
            ++match;
            Lm[i] = true;
        } else {
            for (int j = 0; j < i; ++j) {
                if (used[j]) {
                    Lm[j] = false;
                    Rp[to[j]] = true;
                }
            }
        }
    }

    printf("%d\n", m + n - match);
    int cntL = 0;
    for (int i = 0; i < m; ++i) {
        if (!Lm[i]) {
            ++cntL;
        }
    }
    printf("%d %d\n", cntL, m + n - match - cntL);
    for (int i = 0; i < m; ++i) {
        if (!Lm[i]) {
            printf("%d ", i + 1);
        }
    }
    puts("");
    for (int i = 0; i < n; ++i) {
        if (!Rp[i]) {
            printf("%d ", i + 1);
        }
    }
    puts("");
}

int main() {
    freopen("birthday.in", "r", stdin);
    freopen("birthday.out", "w", stdout);

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; ++i) {
        solve();
    }
}
