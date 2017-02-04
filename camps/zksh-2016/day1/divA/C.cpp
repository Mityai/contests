#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1e4;

const int dx[] = {0, 1};
const int dy[] = {1, 0};

int n, m;
int dp[N][3], to[N];
vector<int> g[N];
vector<string> a;

bool check(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int get(int i, int j) {
    return i * m + j;
}

pair<int, int> rev(int x) {
    return {x / m, x % m};
}

void go(int v, int p) {
    int sum0 = 0;
    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
            dp[v][0] += max(dp[u][0], dp[u][1]);
            sum0 += dp[u][0];
        }
    }
    for (int u : g[v]) {
        if (u != p) {
            if (dp[v][1] < sum0 - dp[u][0] + dp[u][2] + 1) {
                dp[v][1] = sum0 - dp[u][0] + dp[u][2] + 1;
                to[v] = u;
            }
        }
    }
    dp[v][2] = sum0;
}

void ret(int v, int p, int z = -1) {
    if (z == 2) {
        auto posv = rev(v);
        a[posv.fi][posv.se] = 'T';
        for (int u : g[v]) {
            if (u != p) {
                ret(u, v, 0);
            }
        }
    } else if (z == 0 || dp[v][0] >= max(dp[v][1], dp[v][2])) {
        for (int u : g[v]) {
            if (u != p) {
                ret(u, v);
            }
        }
    } else if (dp[v][1] >= max(dp[v][0], dp[v][2])) {
        auto posv = rev(v);
        a[posv.fi][posv.se] = 'T';
        for (int u : g[v]) {
            if (u != p) {
                if (u == to[v]) {
                    ret(u, v, 2);
                } else {
                    ret(u, v, 0);
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);

    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int start = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '.') {
                start = get(i, j);
                for (int k = 0; k < 2; k++) {
                    int newi = i + dx[k];
                    int newj = j + dy[k];
                    if (check(newi, newj) && a[newi][newj] == '.') {
                        g[get(i, j)].push_back(get(newi, newj));
                        g[get(newi, newj)].push_back(get(i, j));
                    }
                }
            }
        }
    }

    if (start != -1) {
        go(start, start);
        ret(start, start);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j + 1 < m && a[i][j] == 'T' && a[i][j + 1] == 'T') {
                a[i][j] = '[', a[i][j + 1] = ']';
            }
            if (i + 1 < n && a[i][j] == 'T' && a[i + 1][j] == 'T') {
                a[i][j] = 'M', a[i + 1][j] = 'W';
            }
        }
    }

    for (auto s : a) {
        cout << s << endl;
    }
}
