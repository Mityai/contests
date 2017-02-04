#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1234567890;

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);

        vector<vector<pair<int, int>>> g(n);
        for (int i = 0; i < m; ++i) {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            --a, --b;
            g[a].push_back({b, w});
            g[b].push_back({a, w});
        }

        vector<pair<int, int>> fam(k + 1);
        for (int i = 1; i <= k; ++i) {
            scanf("%d%d", &fam[i].fi, &fam[i].se);
            --fam[i].fi, --fam[i].se;
        }

        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int st = 0; st < n; ++st) {
            set<pair<int, int>> q;
            auto& d = dist[st];
            q.insert({d[st] = 0, st});
            while (!q.empty()) {
                int v = q.begin()->se;
                q.erase(q.begin());

                for (auto& to : g[v]) {
                    int u = to.fi;
                    int w = to.se;
                    if (d[u] > d[v] + w) {
                        q.erase({d[u], u});
                        q.insert({d[u] = d[v] + w, u});
                    }
                }
            }
        }

        vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(3, vector<int>(n, INF)));

        dp[0][0][0] = 0;
        for (int delivered = 0; delivered <= k; ++delivered) {
            for (int took = 0; took <= 2 && delivered + took <= k; ++took) {
                for (int town = 0; town < n; ++town) {
                    if (dp[delivered][took][town] == INF) continue;
                    if (took > 0 && dist[town][fam[delivered + 1].se] != INF) {
                        dp[delivered + 1][took - 1][fam[delivered + 1].se] = 
                            min(dp[delivered + 1][took - 1][fam[delivered + 1].se],
                                dp[delivered][took][town] + dist[town][fam[delivered + 1].se]);
                    }
                    if (delivered + took + 1 <= k && took + 1 <= 2 && dist[town][fam[delivered + took + 1].fi] != INF) {
                        dp[delivered][took + 1][fam[delivered + took + 1].fi] =
                            min(dp[delivered][took + 1][fam[delivered + took + 1].fi],
                                dp[delivered][took][town] + dist[town][fam[delivered + took + 1].fi]);
                    }
                }
            }
        }

        int ans = INF;
        for (int town = 0; town < n; ++town) {
            ans = min(ans, dp[k][0][town]);
        }

        printf("Case #%d: ", test);
        if (ans == INF) {
            printf("-1\n");
        } else {
            printf("%d\n", ans);
        }
    }
}
