#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const double INF = 1e18;
const int N = 100;
const int MAXS = 1e3;

int n, q;
int E[N], S[N];
int d[N][N];
bool used[N];
vector<pair<int, double>> g[N];
double dans[N][N];

void go(int s) {
    g[s].clear();
    double speed = S[s];
    vector<double> dist(n, INF);
    vector<int> left(n);
    set<pair<double, int>> q;
    left[s] = E[s];
    q.insert({dist[s] = 0, s});
    while (!q.empty()) {
        int v = q.begin()->se;
        q.erase(q.begin());

        for (int u = 0; u < n; ++u) {
            int w = d[v][u];
            if (w != -1) {
                if (left[v] - w >= 0) {
                    if (dist[u] > dist[v] + w / speed || (dist[u] == dist[v] + w && left[v] - w > left[u])) {
                        q.erase({dist[u], u});
                        dist[u] = dist[v] + w / speed;
                        left[u] = left[v] - w;
                        q.insert({dist[u], u});
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i != s && dist[i] != INF) {
            g[s].push_back({i, dist[i]});
        }
    }
}

void dijkstra(int s) {
    for (int i = 0; i < n; ++i) {
        dans[s][i] = INF;
    }
    set<pair<double, int>> q;
    q.insert({dans[s][s] = 0, s});
    while (!q.empty()) {
        int v = q.begin()->se;
        q.erase(q.begin());

        for (auto to : g[v]) {
            int u = to.fi;
            double w = to.se;
            if (dans[s][u] > dans[s][v] + w) {
                q.erase({dans[s][u], u});
                dans[s][u] = dans[s][v] + w;
                q.insert({dans[s][u], u});
            }
        }
    }
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        scanf("%d%d", &n, &q);

        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &E[i], &S[i]);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &d[i][j]);
            }
        }

        for (int i = 0; i < n; ++i) {
            go(i);
        }

        printf("Case #%d: ", test);

        memset(used, false, n * sizeof(used[0]));
        for (int i = 0; i < q; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            if (!used[u]) {
                dijkstra(u);
                used[u] = true;
            }
            printf("%.10lf ", dans[u][v]);
        }
        puts("");
    }
}
