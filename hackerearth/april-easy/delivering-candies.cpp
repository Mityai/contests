#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX - 1234567890;

const int N = 1e5;

vector< pair<int, int> > g[N];

bool mark[N];
int K[N];
ll allK = 0;

void dfs(int v) {
    mark[v] = true;
    allK += K[v];
    for (auto to : g[v]) {
        int u = to.fi;
        if (!mark[u]) {
            dfs(u);
        }
    }
}

int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    --s;

    for (int i = 0; i < n; i++) {
        scanf("%d", K + i);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        ll w;
        scanf("%d%d%lld", &a, &b, &w);
        --a, --b;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    dfs(s);

    vector<ll> dist(n, INF);
    set< pair<ll, int> > q;
    q.insert({dist[s] = 0, s});

    while (!q.empty()) {
        int v = q.begin()->se;
        q.erase(q.begin());

        for (auto to : g[v]) {
            int u = to.fi;
            ll w = to.se;
            if (dist[u] > dist[v] + w) {
                q.erase({dist[u], u});
                dist[u] = dist[v] + w;
                q.insert({dist[u], u});
            }
        }
    }

    ll sumdist = 0;
    for (int i = 0; i < n; i++) {
        if (mark[i]) {
            sumdist += K[i] * dist[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (!mark[i]) {
            printf("0 ");
        } else {
            ll oth = allK - K[i];
            ll ans = oth * dist[i] + sumdist - K[i] * dist[i];
            printf("%lld ", ans);
        }
    }
    puts("");
}
