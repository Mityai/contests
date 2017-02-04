#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int N = 3e5;
const int K = 500;

vector<int> g[N];
int en[N], ex[N], depth[N];
int ans[N], sumx[N], sumk[N];
int T = 0;

void dfs(int v, int p) {
    en[v] = T++;
    for (int u : g[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
    ex[v] = T++;
}

bool isAnc(int a, int b) {
    return en[a] <= en[b] && ex[b] <= ex[a];
}

struct Q {
    int v, x, k;
};

inline int sum(int a, int b) {
    int ret = a + b;
    if (ret >= MOD) ret -= MOD;
    return ret;
}

inline int sub(int a, int b) {
    int ret = a - b;
    if (ret < 0) ret += MOD;
    return ret;
}

void go(int v, int p, int curx, int curk, int addk) {
    curx = sum(curx, sumx[v]);
    sumx[v] = 0;
    addk = sum(addk, sumk[v]);

    ans[v] = sum(ans[v], sub(curx, curk));

    for (int u : g[v]) {
        if (u != p) {
            go(u, v, curx, sum(curk, addk), addk);
        }
    }
    sumk[v] = 0;
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
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

    int q;
    scanf("%d", &q);

    vector<Q> todo;
    todo.reserve(K);
    for (int i = 1; i <= q; i++) {

        int type;
        scanf("%d", &type);
        
        if (type == 1) {
            Q q;
            scanf("%d%d%d", &q.v, &q.x, &q.k);
            --q.v;
            sumx[q.v] = sum(sumx[q.v], q.x);
            sumk[q.v] = sum(sumk[q.v], q.k);
            todo.push_back(q);
        } else {
            if ((int)todo.size() >= K) {
                go(0, 0, 0, 0, 0);
                todo.clear();
            }
            int v;
            scanf("%d", &v);
            --v;
            int cur = ans[v];
            for (Q q : todo) {
                if (isAnc(q.v, v)) {
                    cur = sum(cur, sub(q.x, ((depth[v] - depth[q.v]) * 1LL * q.k) % MOD));
                }
            }
            printf("%d\n", cur);
        }
    }
}
