#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int MAXN = 1e5;

int N, M, X, A, C, MOD;

inline int get() {
    X = (X * 1LL * A + C) % MOD;
    return X;
}

int p[MAXN], rnk[MAXN];

int root(int v) {
    return p[v] == v ? v : p[v] = root(p[v]);
}

void unite(int v, int u) {
    v = root(v);
    u = root(u);
    if (rnk[v] < rnk[u]) swap(v, u);
    p[u] = v;
    if (rnk[v] == rnk[u]) rnk[v]++;
}

int main() {
    scanf("%d%d%d%d%d%d", &N, &M, &X, &A, &C, &MOD);

    for (int i = 0; i < N; i++) p[i] = i;

    set< pair< int, pair<int, int> > > ed;
    map< pair<int, int>, int > we;

    for (int i = 0; i < M; i++) {
        int u = get() % N;
        int v = get() % N;
        if (v > u) swap(v, u);
        int w = get();
        if (we.find({v, u}) != we.end()) {
            if (we[{v, u}] <= w) continue;
        }
        we[{v, u}] = w;
        if (ed.size() == MAXN && ed.rbegin()->fi > w) {
            ed.erase(--ed.end());
            ed.insert({w, {v, u}});
        } else if (ed.size() < MAXN) {
            ed.insert({w, {v, u}});
        }
    }

    ll ans = 0;
    while (!ed.empty()) {
        auto e = *ed.begin();
        ed.erase(ed.begin());
        int w = e.fi;
        int v = e.se.fi;
        int u = e.se.se;
        if (root(v) != root(u)) {
            ans += w;
            unite(v, u);
        }
    }
    
    printf("%lld\n", ans);
}
