
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
   
typedef long long ll;
   
const ll INF = LLONG_MAX / 100;
 
vector< vector< pair<int, ll> > > g;
vector<ll> dist;
   
void dijkstra(int start) {
    int n = (int)g.size();
    set< pair<ll, int> > q;
    q.insert({dist[start] = 0, start});
    bool used[n];
    memset(used, 0, sizeof used);
    while (!q.empty()) {
        auto v = q.begin()->se;
        q.erase(q.begin());

        used[v] = true;
   
        for (auto to : g[v]) {
            int u = to.fi;
            ll w = to.se;
            if (w != INF && dist[u] > dist[v] + w) {
                q.erase({dist[u], u});
                dist[u] = dist[v] + w;
                q.insert({dist[u], u});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) dist[i] = -1;
    }
}
 
void solveall(int n, int m) {
    int T[m], A[m], B[m]; ll C[m];
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%lld", &T[i], &A[i], &B[i], &C[i]);
        --A[i], --B[i];
    }
   
    int MAXN = n + n + m;
    g.resize(MAXN);
    int fictive[n];
    memset(fictive, -1, sizeof fictive);
    ll minfor[n];
    for (int i = 0; i < n; i++) {
        fictive[i] = i + n;
        minfor[i] = INF;
        g[i].push_back({fictive[i], INF});
    }
    int tc = n + n;
 
    for (int ii = 0; ii < m; ii++) {
        int t = T[ii], a = A[ii], b = B[ii]; ll c = C[ii];
        int newfict = tc++;
        if (t == 1) {
            minfor[a] = min(g[a][0].se, c);
            g[newfict].push_back({fictive[a], g[a][0].se - minfor[a]});
            fictive[a] = newfict;
            g[a][0] = {fictive[a], minfor[a]};
            g[fictive[a]].push_back({b, c - minfor[a]});
        } else {
            c += minfor[a];
            minfor[b] = min(g[b][0].se, c);
            g[newfict].push_back({fictive[b], g[b][0].se - minfor[b]});
            fictive[b] = newfict;
            g[b][0] = {fictive[b], minfor[b]};
            g[fictive[b]].push_back({fictive[a], c - minfor[b]});
        }
    }
 
    dist.resize(MAXN, INF);
    dijkstra(0);
    for (int i = 1; i < n; i++) {
        printf("%lld\n", dist[i]);
    }
}
 
int main() {
    freopen("olympair.dat", "r", stdin);
    freopen("olympair.sol", "w", stdout);
   
    int n, m;
    scanf("%d%d", &n, &m);
  
    solveall(n, m);
}
