#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 3e5;
const int MOD = 1e9 + 7;

inline int add(int a, int b) {
    int ret = a + b;
    if (ret >= MOD) ret -= MOD;
    return ret;
}

inline int sub(int a, int b) {
    int ret = a - b;
    if (ret < 0) ret += MOD;
    return ret;
}

struct Fenwick {
    int n;
    vector<int> fenw;

    Fenwick() {}
    Fenwick(int n) : n(n) {
        fenw.resize(n);
    }

    void addval(int pos, int val) {
        for (int i = pos; i < n; i = (i | (i + 1))) {
            fenw[i] = add(fenw[i], val);
        }
    }

    int sum(int pos) {
        int ret = 0;
        for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
            ret = add(ret, fenw[i]);
        }
        return ret;
    }
} fnwX[N], fnwK[N], fnwKU[N];

vector<int> g[N];
int pos[N], par[N], sz[N], no[N], top[N], len[N], depth[N];
int tc = 0;

void dfs(int v, int p) {
    par[v] = p;
    depth[v] = depth[p] + 1;
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sz[v] += sz[u];
        }
    }
}

void go(int v, int p) {
    if (v == p || 2 * sz[v] <= sz[p]) {
        no[v] = tc++;
        top[no[v]] = v;
    } else {
        no[v] = no[p];
    }
    pos[v] = len[no[v]]++;

    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
}

void add(int v, int x, int k) {
    fnwX[no[v]].addval(pos[v], x);
    fnwK[no[v]].addval(pos[v], k);
    fnwKU[no[v]].addval(pos[v], ((ll)depth[v] * k) % MOD);
}

int ask(int v) {
    int u = v;
    int sumx = 0, sumk = 0, sumku = 0;
    while (true) {
        sumx = add(sumx, fnwX[no[v]].sum(pos[v]));
        sumk = add(sumk, fnwK[no[v]].sum(pos[v]));
        sumku = add(sumku, fnwKU[no[v]].sum(pos[v]));
        if (no[par[top[no[v]]]] == no[v]) break;
        v = par[top[no[v]]];
    }
    //printf("v = %d sumX = %d sumK = %d sumKU = %d\n", u, sumx, sumk, sumku);
    int ret = sumx;
    ret = sub(ret, ((ll)sumk * depth[u]) % MOD);
    ret = add(ret, sumku);
    return ret;
}

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        --p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    dfs(0, 0);
    go(0, 0);

    for (int i = 0; i < tc; i++) {
        fnwX[i] = Fenwick(len[i]);
        fnwK[i] = Fenwick(len[i]);
        fnwKU[i] = Fenwick(len[i]);
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int v, x, k;
            scanf("%d%d%d", &v, &x, &k);
            --v;
            add(v, x, k);
        } else {
            int v;
            scanf("%d", &v);
            --v;
            printf("%d\n", ask(v));
        }
    }
}
