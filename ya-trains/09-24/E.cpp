#include <bits/stdc++.h> 
#define fi first
#define se second
using namespace std;

using ll = long long;

const int MAXFIG = 16;

struct Fig {
    int t, i, j;
};

const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

const int fx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int fy[] = {0, 1, 1, 1, 0, -1, -1, -1};

int n, m;
vector<Fig> a;

int num[MAXFIG][MAXFIG];
bool can[1 << MAXFIG][MAXFIG][MAXFIG];
int help[1 << MAXFIG][MAXFIG][MAXFIG];
int dp[1 << MAXFIG][MAXFIG];
int bfs[MAXFIG][MAXFIG];

bool in(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            int t = -1;
            if (s[j] == '*') {
                t = 0;
            } else if (s[j] == 'K') {
                t = 1;
            } else if (s[j] == 'B') {
                t = 2;
            } else if (s[j] == 'R') {
                t = 3;
            }
            if (t != -1) {
                a.push_back({t, i, j});
            }
        }
    }

    sort(a.begin(), a.end(), [](const Fig& a, const Fig& b) { return a.t < b.t; });
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) num[i][j] = -1;
    for (int i = 0; i < (int)a.size(); i++) {
        auto& f = a[i];
        num[f.i][f.j] = i;
    }

    int k = a.size();
    int M = (1 << k);

    for (int mask = 0; mask < M; mask++) {
        for (int cur = 0; cur < k; cur++) {
            if ((mask >> cur) & 1) {
                if (a[cur].t == 1) {
                    for (int i = 0; i < 8; i++) {
                        int newi = a[cur].i + dx[i];
                        int newj = a[cur].j + dy[i];
                        if (in(newi, newj)) {
                            if (num[newi][newj] == -1 || !((mask >> num[newi][newj]) & 1)) {
                                can[mask][newi][newj] = true;
                            }
                        }
                    }
                } else if (a[cur].t == 2) {
                    int i = a[cur].i;
                    int j = a[cur].j;
                    for (int s1 = -1; s1 <= 1; s1 += 2) {
                        for (int s2 = -1; s2 <= 1; s2 += 2) {
                            for (int t = 1; t <= n + m; t++) {
                                int newi = i + s1 * t;
                                int newj = j + s2 * t;
                                if (in(newi, newj)) {
                                    if (num[newi][newj] != -1 && ((mask >> num[newi][newj]) & 1)) {
                                        break;
                                    }
                                    can[mask][newi][newj] = true;
                                } else break;
                            }
                        }
                    }
                } else if (a[cur].t == 3) {
                    for (int newi = a[cur].i + 1; newi < n + m; newi++) {
                        int newj = a[cur].j;
                        if (in(newi, newj)) {
                            if (num[newi][newj] != -1 && ((mask >> num[newi][newj]) & 1)) {
                                break;
                            }
                            can[mask][newi][newj] = true;
                        } else break;
                    }
                    for (int newi = a[cur].i - 1; newi >= 0; newi--) {
                        int newj = a[cur].j;
                        if (in(newi, newj)) {
                            if (num[newi][newj] != -1 && ((mask >> num[newi][newj]) & 1)) {
                                break;
                            }
                            can[mask][newi][newj] = true;
                        } else break;
                    }
                    for (int newj = a[cur].j + 1; newj < n + m; newj++) {
                        int newi = a[cur].i;
                        if (in(newi, newj)) {
                            if (num[newi][newj] != -1 && ((mask >> num[newi][newj]) & 1)) {
                                break;
                            }
                            can[mask][newi][newj] = true;
                        } else break;
                    }
                    for (int newj = a[cur].j - 1; newj >= 0; newj--) {
                        int newi = a[cur].i;
                        if (in(newi, newj)) {
                            if (num[newi][newj] != -1 && ((mask >> num[newi][newj]) & 1)) {
                                break;
                            }
                            can[mask][newi][newj] = true;
                        } else break;
                    }
                }
            }
        }
    }

    for (int mask = 0; mask < M; mask++) {
        for (int v = 0; v < k; v++) {
            for (int u = 0; u < k; u++) help[mask][v][u] = INT_MAX;
            if (!((mask >> v) & 1)) {
                for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) bfs[i][j] = INT_MAX;
                bfs[a[v].i][a[v].j] = 0;
                queue< pair<int, int> > q;
                q.push({a[v].i, a[v].j});
                while (!q.empty()) {
                    int curi = q.front().fi;
                    int curj = q.front().se;
                    q.pop();
                    if (num[curi][curj] != -1 && ((mask >> num[curi][curj]) & 1)) continue;
                    for (int f = 0; f < 8; f++) {
                        int newi = curi + fx[f];
                        int newj = curj + fy[f];
                        if (in(newi, newj)) {
                            if (!can[mask][newi][newj] && bfs[newi][newj] == INT_MAX) {
                                if (num[newi][newj] != -1 && ((mask >> num[newi][newj]) & 1)) {
                                    if (!can[mask ^ (1 << num[newi][newj])][newi][newj]) {
                                        bfs[newi][newj] = bfs[curi][curj] + 1;
                                        q.push({newi, newj});
                                    }
                                } else {
                                    bfs[newi][newj] = bfs[curi][curj] + 1;
                                    q.push({newi, newj});
                                }
                            }
                        }
                    }
                }
                for (int to = 0; to < k; to++) {
                    help[mask][v][to] = bfs[a[to].i][a[to].j];
                }
            }
        }
    }

    vector< vector<int> > masks(k + 1);
    for (int i = 0; i < M; i++) {
        masks[__builtin_popcount(i)].push_back(i);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < k; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[(M - 1) ^ 1][0] = 0;
    for (int i = k; i >= 0; i--) {
        for (int mask : masks[i]) {
            for (int v = 0; v < k; v++) {
                if (!((mask >> v) & 1) && dp[mask][v] != INT_MAX) {
                    for (int to = 0; to < k; to++) {
                        if ((mask >> to) & 1) {
                            if (help[mask][v][to] != INT_MAX) {
                                dp[mask ^ (1 << to)][to] = min(dp[mask ^ (1 << to)][to], dp[mask][v] + help[mask][v][to]);
                            }
                        }
                    }
                }
            }
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i < k; i++) {
        ans = min(ans, dp[0][i]);
    }

    if (ans == INT_MAX) {
        puts("-1");
    } else {
        printf("%d\n", ans);
    }
}
