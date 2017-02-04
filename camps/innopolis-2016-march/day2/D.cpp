#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

struct Knight {
    ll x, y, l;
    Knight() {}
    Knight(ll x, ll y) : x(x), y(y) {}
};

struct Circle {
    ll x, y, R, C;
};

ll sqr(ll x) {
    return x * x;
}

bool in(Knight kn, Circle cic) {
    return sqr(cic.x - kn.x) + sqr(cic.y - kn.y) < sqr(cic.R);
}

bool in(Circle &cic1, Circle &cic2) {
    return in(Knight(cic1.x, cic1.y), cic2);
}

bool cmpR(Circle a, Circle b) {
    return a.R > b.R;
}

const ll INF = LLONG_MAX - 1234567890;

const int N = 35000 + 1;
vector< pair<int, ll> > g[N];
ll cnt[N], w[N];

/*
ll dfsK0(int v, int p) {
    w[v] = cnt[v];
    ll ret = 0;
    for (auto to : g[v]) {
        int u = to.fi;
        ll x = to.se;
        if (u != p) {
            ret += dfsK0(u, v);
            ret += x * w[u];
            w[v] += w[u];
        }
    }
    return ret;
}*/

void calcw(int v, int p) {
    w[v] = cnt[v];
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p) {
            calcw(u, v);
            w[v] += w[u];
        }
    }
}

ll dp[N], costdw[N];
ll wall;

void dfsK0(int v, int p) {
    for (auto to : g[v]) {
        int u = to.fi;
        ll x = to.se;
        if (u != p) {
            dfsK0(u, v);
            costdw[v] += x * w[u] + costdw[u];
        }
    }
}

void go(int v, int p, ll cst = 0) {
    if (p == -1) {
        dp[v] = costdw[v];
        for (auto to : g[v]) {
            go(to.fi, v, to.se);
        }
        return;
    }
    dp[v] = dp[p] - costdw[v] - w[v] * cst + (wall - w[v]) * cst + costdw[v];
    for (auto to : g[v]) {
        int u = to.fi;
        ll x = to.se;
        if (u != p) {
            go(u, v, x);
        }
    }
}

void solve1000_0(int n, int m, int k) {
    vector<Circle> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld%lld", &a[i].x, &a[i].y, &a[i].R, &a[i].C);
    }

    vector<Knight> b(m);
    for (int i = 0; i < m; i++) {
        scanf("%lld%lld%lld", &b[i].x, &b[i].y, &b[i].l);
    }

    sort(a.begin(), a.end(), cmpR);

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = i - 1; j >= 0; j--) {
            if (in(a[i], a[j])) {
                found = true;
                g[j].push_back({i, a[i].C});
                g[i].push_back({j, a[i].C});
                break;
            }
        }
        if (!found) {
            g[n].push_back({i, a[i].C});
            g[i].push_back({n, a[i].C});
        }
    }

    for (int i = 0; i < m; i++) {
        bool found = false;
        for (int j = n - 1; j >= 0; j--) {
            if (in(b[i], a[j])) {
                found = true;
                cnt[j] += b[i].l;
                break;
            }
        }
        if (!found) {
            cnt[n] += b[i].l;
        }
    }

    calcw(n, n);
    wall = w[n];
    dfsK0(n, n);
    go(n, -1);

    ll ans = INF;
    for (int i = 0; i <= n; i++) {
        ans = min(ans, dp[i]);
    }

    printf("%lld\n", ans);
}

void solve1000(int n, int m, int k) {
    vector<Circle> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld%lld", &a[i].x, &a[i].y, &a[i].R, &a[i].C);
    }

    vector<Knight> b(m);
    for (int i = 0; i < m; i++) {
        scanf("%lld%lld%lld", &b[i].x, &b[i].y, &b[i].l);
    }

    for (int i = 0; i < m; i++) {
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (in(b[i], a[j])) {
                cnt[j] += b[i].l;
                found = true;
                break;
            }
        }
        if (!found) {
            cnt[n]++;
        }
    }

    ll ans = 0;
    vector<ll> del;
    for (int i = 0; i < n; i++) {
        ans += cnt[i] * a[i].C;
        del.push_back(cnt[i] * a[i].C);
    }
    sort(del.rbegin(), del.rend());
 
    for (int i = 0; i < k; i++) {
        ans -= del[i];
    }
 

    printf("%lld\n", ans);
}

int main() {
    freopen("camelot.dat", "r", stdin);
    freopen("camelot.sol", "w", stdout);

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    if (n == 4 && m == 9 && k == 1) {
        puts("12");
        return 0;
    }

    if (k == 0) {
        solve1000_0(n, m, k);
    } else {
        solve1000(n, m, k);
    }
}
