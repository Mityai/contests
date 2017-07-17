#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

const ll INF = 1e18;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

void solve(int r, int c, int n, int d) {
    vector<vector<ll>> minw(r, vector<ll>(c, 1));
    vector<vector<ll>> maxw(r, vector<ll>(c, INF));

    for (int t = 0; t < n; ++t) {
        int x, y, b;
        scanf("%d%d%d", &x, &y, &b);
        --x, --y;

        minw[x][y] = maxw[x][y] = b;
        vector<vector<char>> used(r, vector<char>(c, false));
        queue<pair<int, int>> q;
        used[x][y] = true;
        q.push({x, y});
        while (!q.empty()) {
            auto v = q.front();
            q.pop();

            for (int k = 0; k < 4; ++k) {
                int newi = v.fi + dx[k];
                int newj = v.se + dy[k];
                if (0 <= newi && newi < r) {
                    if (0 <= newj && newj < c) {
                        if (!used[newi][newj]) {
                            minw[newi][newj] = max(minw[newi][newj], minw[v.fi][v.se] - d);
                            maxw[newi][newj] = min(maxw[newi][newj], maxw[v.fi][v.se] + d);
                            used[newi][newj] = true;
                            q.push({newi, newj});
                        }
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (minw[i][j] > maxw[i][j]) {
                puts("IMPOSSIBLE");
                return;
            }
            ans += maxw[i][j];
        }
    }
    printf("%lld\n", ans % MOD);
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int TEST;
    scanf("%d", &TEST);

    for (int test = 1; test <= TEST; ++test) {
        int r, c, n, d;
        scanf("%d%d%d%d", &r, &c, &n, &d);

        printf("Case #%d: ", test);
        solve(r, c, n, d);
    }
}
