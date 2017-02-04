#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX;
const int INF_INT = INT_MAX;

struct To {
    int u, w, i;
};

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    //freopen("prof.in", "r", stdin);
    //freopen("prof.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    vector< vector<To> > g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        g[u].push_back({v, w, i});
        g[v].push_back({u, w, i});
    }

    int s;
    scanf("%d", &s);
    --s;

    vector<ll> d(n, INF);
    d[s] = 0;

    vector<ll> sum(n, INF);
    sum[s] = 0;

    set< pair<ll, int > > q;
    q.insert({d[s], s});

    vector<int> lastid(n, -1);
    vector<int> lastdist(n, INF_INT);

    ll ans = 0;
    vector<int> ids;

    while (!q.empty()) {
        int v = q.begin()->se;
        q.erase(q.begin());

        if (lastid[v] != -1) {
            ids.push_back(lastid[v]);
            ans += lastdist[v];
        }

        for (int i = 0; i < (int)g[v].size(); i++) {
            int u = g[v][i].u;
            int w = g[v][i].w;

            if (d[u] > d[v] + w || (d[u] == d[v] + w && ans + w < ans + lastdist[u])) {
                q.erase({d[u], u});
                d[u] = d[v] + w;
                lastid[u] = g[v][i].i;
                lastdist[u] = w;
                q.insert({d[u], u});
            }
        }
    }

    printf("%lld\n", ans);
    for (int id : ids) {
        printf("%d ", id + 1);
    }
}
