#include <bits/stdc++.h>
#define rank ljasdf
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX - 1234567890;

ll sol() {
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

    vector<ll> dist(n, INF);
    set< pair<ll, int> > q;
    q.insert({dist[0] = 0, 0});
    while (!q.empty()) {
        int v = q.begin()->se;
        q.erase(q.begin());

        for (auto to : g[v]) {
            int u = to.fi;
            int w = to.se;
            if (dist[u] > dist[v] + w) {
                q.erase({dist[u], u});
                dist[u] = dist[v] + w;
                q.insert({dist[u], u});
            }
        }
    }
    return dist[n - 1];
}


void solve1() {
    printf("%lld\n", sol() + sol());
}

const int N = 5e4;

int p[2][N], rank[2][N];

int get(int f, int v) {
    return v == p[f][v] ? v : p[f][v] = get(f, p[f][v]);
}

vector< set<int> > q(2);

void unite(int f, int v, int u) {
    v = get(f, v);
    u = get(f, u);

    if (rank[f][v] < rank[f][u]) swap(v, u);
    q[f].erase(v);
    q[f].erase(u);
    p[f][u] = v;
    q[f].insert(v);
    if (rank[f][v] == rank[f][u]) rank[f][v]++;
}

struct Edge {
    int a, b, w, f;
};

bool cmp(Edge e1, Edge e2) {
    return e1.w < e2.w;
}

void solve2() {
    int n[2], m[2];
    vector<Edge> e;

    for (int k = 0; k < 2; k++) {
        scanf("%d%d", &n[k], &m[k]);

        for (int j = 0; j < n[k]; j++) {
            p[k][j] = j;
            q[k].insert(j);
        }

        for (int i = 0; i < m[k]; i++) {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            --a, --b;
            e.push_back({a, b, w, k});
        }
    }

    sort(e.begin(), e.end(), cmp);
    ll ans = 0;
    int sz[2] = {(int)q[0].size(), (int)q[1].size()};
    for (int i = 0; i < (int)e.size(); i++) {
        int a = e[i].a, b = e[i].b, w = e[i].w, f = e[i].f;
        a = get(f, a);
        b = get(f, b);
        sz[0] = q[0].size();
        sz[1] = q[1].size();
        if (a != b) {
            ans += (ll)w * sz[1 - f];
            unite(f, a, b);
        }
    }

    printf("%lld\n", ans);
}

int main() {
    freopen("cartesius.dat", "r", stdin);
    freopen("cartesius.sol", "w", stdout);

    int TYPE;
    while (scanf("%d", &TYPE) == 1) {
        if (TYPE == 1) {
            solve1();
        } else {
            solve2();
            return 0;
        }
    }
}
