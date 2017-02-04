#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1234567890;

int main() {
    freopen("ideal.in", "r", stdin);
    freopen("ideal.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    vector< vector< pair<int, int> > > g(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    vector<int> dist(n, INF), col(n, INF), p(n, -1), ord(n, INF);
    dist[0] = 0;
    ord[0] = 0;
    queue<int> q;
    q.push(0);
    vector< pair< pair<int, int>, int > > recalc;
    vector<int> torecalc;

    int lastd = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (dist[v] != lastd) {
            for (int w : torecalc) {
                recalc.push_back({{ord[p[w]], col[w]}, w});
            }
            sort(recalc.begin(), recalc.end());
            for (int i = 0, y = 0; i < (int)recalc.size(); i++) {
                auto x = recalc[i];
                if (i > 0 && x.fi != recalc[i - 1].fi) {
                    y++;
                }
                ord[x.se] = y;
            }
            recalc.clear();
            torecalc.clear();
            lastd = dist[v];
        }
        
        for (auto to : g[v]) {
            int u = to.fi, c = to.se;
            //if (u + 1 == 6) cout << v << ' ' << ord[v] << endl;
            if (dist[u] > dist[v] + 1) {
                dist[u] = dist[v] + 1;
                col[u] = c;
                torecalc.push_back(u);
                q.push(u);
                p[u] = v;
            } else if (dist[u] == dist[v] + 1 && (ord[p[u]] > ord[v] || (ord[p[u]] == ord[v] && col[u] > c))) {
                col[u] = c;
                p[u] = v;
            }
        }
    }

    vector<int> ans;
    for (int i = n - 1; p[i] != -1; i = p[i]) {
        ans.push_back(col[i]);
    }
    reverse(ans.begin(), ans.end());
    
    printf("%d\n", (int)ans.size());
    for (int x : ans) {
        printf("%d ", x);
    }
    puts("");
}
