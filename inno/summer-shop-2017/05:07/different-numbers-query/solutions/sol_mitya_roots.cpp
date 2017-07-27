#ifdef LOCAL
//#  define _GLIBCXX_DEBUG
#else
#  define cerr __get_ce
#endif
#include <bits/stdc++.h>

using namespace std;
#define next __next
#define prev __prev
#define right __right
#define left __left
#define index __index

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

typedef pair<int, int> ipair;
#define szof(x) ((int)(x).size())
#define bend(x) (x).begin(), (x).end()

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
mt19937 tw(960172);

bool is_prime(ll x) { for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return x > 1; }
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }
ll sqr(int a) { return (ll) a * a; } template<class T> T sqr(T const& a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }

int const N = 100100;
int const SZ = 1 << 17;
int const C = 777;
int const LOG = 19;

int n;
vector<pair<int, int>> g[N];

namespace {
    int edge_num[N];
    bool was[N];
    int tree[SZ * 2 + 1];
    int cnt[N];

    void change(int eind) {
        int pos = edge_num[eind];
        if (pos >= SZ)
            return;
        if (was[eind]) {
            --cnt[pos];
            was[eind] = false;
        } else {
            ++cnt[pos];
            was[eind] = true;
        }
        int v = pos + SZ;
        tree[v] = cnt[pos] == 0 ? 0 : 1;
        for (v /= 2; v > 0; v /= 2) {
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }
    
    int calc_mex() {
        int v = 1, l = 0, r = SZ;
        assert(tree[v] < n);
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (tree[2 * v] < m - l) {
                v = 2 * v;
                r = m;
            } else {
                v = 2 * v + 1;
                l = m;
            }
        }
        assert(tree[v] == 0);
        return l;
    }
}

int tin[N], d[N], up[LOG][N], eto[N];
vector<int> tour;

void dfs(int v) {
    tour.push_back(v);
    tin[v] = tour.size();
    for (int i = 1; i < LOG; ++i) {
        int x = up[i - 1][v];
        up[i][v] = up[i - 1][x];
    }
    for (auto e : g[v]) {
        int to = e.first;
        if (tin[to] == 0) {
            d[to] = d[v] + 1;
            up[0][to] = v;
            eto[to] = e.second;
            dfs(to);
        }
    }
}

int go_up(int v, int d) {
    if (d <= 0)
        return v;
    for (int i = 0; d > 0; ++i, d /= 2)
        if (d & 1)
            v = up[i][v];
    return v;
}

int get_lca(int a, int b) {
    a = go_up(a, d[a] - d[b]);
    b = go_up(b, d[b] - d[a]);
    if (a == b)
        return a;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[i][a] != up[i][b]) {
            a = up[i][a];
            b = up[i][b];
        }
    }
    return up[0][a];
}

inline void go(int a, int par) {
    while (a != par) {
        change(eto[a]);
        a = up[0][a];
    }
}

int qa[N], qb[N], ans[N];
vector<int> curqs[N];

void go(int v, int par, int root) {
    for (int x : curqs[v]) {
        int lca = get_lca(root, qa[x]);
        go(root, lca);
        go(qa[x], lca);
        ans[x] = calc_mex();
        go(root, lca);
        go(qa[x], lca);
    }
    for (auto e : g[v]) {
        int to = e.first;
        if (to != par) {
            change(e.second);
            go(to, v, root);
            change(e.second);
        }
    }
}

void solve() {
    int q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
        edge_num[i] = w;
    }
    d[0] = 0;
    up[0][0] = 0;
    dfs(0);
    static pair<int, int> dist[N];
    vector<int> roots;
    for (int i = 0; i < n; i += C)
        roots.push_back(tour[i]);
    if (roots.back() != tour.back())
        roots.push_back(tour.back());
    {
        fill(dist, dist + n, make_pair(INF, -1));
        static int q[N];
        int tail = 0;
        for (int v : roots)
            dist[q[tail++] = v] = {0, v};
        for (int i = 0; i < tail; ++i) {
            int v = q[i];
            for (auto e : g[v]) {
                int to = e.first;
                if (dist[to].first == INF) {
                    dist[to] = dist[v];
                    ++dist[to].first;
                    q[tail++] = to;
                }
            }
        }
    }
    static int root[N];
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", qa + i, qb + i);
        --qa[i];
        --qb[i];
        if (dist[qa[i]] > dist[qb[i]])
            swap(qa[i], qb[i]);
        root[i] = dist[qa[i]].second;
    }
    for (int v : roots) {
        for (int i = 0; i < n; ++i)
            curqs[i].clear();
        for (int i = 0; i < q; ++i)
            if (root[i] == v)
                curqs[qb[i]].push_back(i);
        go(v, -1, v);
    }
    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
}

int main() {
    //freopen("", "r", stdin);
    //freopen("", "w", stdout);
    cout << setprecision(15) << fixed;
#ifdef LOCAL
    cerr << setprecision(6) << fixed;
#endif
    int tcnt = 1;
    //scanf("%d", &tcnt);
    for (int test = 1; test <= tcnt; ++test)
        solve();
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}
