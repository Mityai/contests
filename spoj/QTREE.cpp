#include <bits/stdc++.h>
#define ref jlasdf
#define mp make_pair
#define nullptr NULL
#define fi first
#define se second
using namespace std;
 
const int N = 1e4;
const int K = 15;
const int INF = 1234567890;
 
vector< pair<int, int> > g[N];
vector<int> sa[N];
int ref[N], weight[N], no[N], len[N], top[N], pos[N], sz[N], up[N][K], en[N], ex[N], val[N];
int tc = 0;
int T = 0;
 
struct Node {
    Node *l, *r;
    int L, R;
    int mx;
 
    Node() : l(nullptr), r(nullptr), L(0), R(0), mx(-INF) {}
    Node(int L, int R, int mx) : l(nullptr), r(nullptr), L(L), R(R), mx(mx) {}
    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        mx = max(l->mx, r->mx);
    }
} *tree[N];
 
Node *buildTree(int L, int R, int num) {
    if (R - L == 1) return new Node(L, R, sa[num][L]);
    int M = (L + R) >> 1;
    return new Node(buildTree(L, M, num), buildTree(M, R, num));
}
 
int getmax(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) return -INF;
    if (L <= node->L && node->R <= R) return node->mx;
    return max(getmax(node->l, L, R), getmax(node->r, L, R));
}
 
void setval(Node *node, int pos, int newval) {
    if (node->R - node->L == 1) {
        node->mx = newval;
        return;
    }
    if (pos < node->l->R) setval(node->l, pos, newval);
    else setval(node->r, pos, newval);
    node->mx = max(node->l->mx, node->r->mx);
}
 
void dfs(int v, int p) {
    en[v] = T++;
    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
 
    sz[v] = 1;
    for (int i = 0; i < (int)g[v].size(); i++) {
        int u = g[v][i].fi;
        int id = g[v][i].se;
        int w = weight[id];
        if (u != p) {
            ref[id] = u;
            val[u] = w;
            dfs(u, v);
            sz[v] += sz[u];
        }
    }
    ex[v] = T++;
}
 
void go(int v, int p = -1) {
    if (p == -1 || 2 * sz[v] <= sz[p]) {
        no[v] = tc++;
        top[no[v]] = v;
    } else {
        no[v] = no[p];
    }
    pos[v] = len[no[v]]++;
    sa[no[v]].push_back(val[v]);
 
    for (int i = 0; i < (int)g[v].size(); i++) {
        int u = g[v][i].fi;
        if (u != p) {
            go(u, v);
        }
    }
}
 
bool isAnc(int a, int b) {
    return en[a] <= en[b] && ex[b] <= ex[a];
}
 
int getlca(int v, int u) {
    for (int i = K - 1; i >= 0; i--) {
        if (!isAnc(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return isAnc(v, u) ? v : up[v][0];
}
 
void change(int id, int newval) {
    int v = ref[id];
    setval(tree[no[v]], pos[v], newval);
}
 
int maxtolca(int v, int u) {
    int ret = -INF;
    while (no[v] != no[u]) {
        ret = max(ret, getmax(tree[no[v]], 0, pos[v] + 1));
        v = up[top[no[v]]][0];
    }
    if (v != u) ret = max(ret, getmax(tree[no[v]], pos[u] + 1, pos[v] + 1));
    return ret;
}
 
int maxpath(int v, int u) {
    int lca = getlca(v, u);
    return max(maxtolca(v, lca), maxtolca(u, lca));
}
 
void clear(int n) {
    for (int i = 0; i < N; i++) g[i].clear(), sa[i].clear();
    memset(len, 0, n * sizeof(len[0]));
    tc = 0;
    T = 0;
}
 
void solve() {
    int n;
    scanf("%d", &n);
 
    clear(n);
 
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        g[a].push_back(mp(b, i));
        g[b].push_back(mp(a, i));
        weight[i] = w;
        assert(w >= 0);
    }
 
    dfs(0, 0);
    go(0);
 
    for (int i = 0; i < tc; i++) {
        tree[i] = buildTree(0, len[i], i);
    }
 
    char s[10];
    while (scanf(" %s", s)) {
        if (s[0] == 'Q') {
            int a, b;
            scanf("%d%d", &a, &b);
            --a, --b;
            printf("%d\n", maxpath(a, b));
        } else if (s[0] == 'C') {
            int id, newval;
            scanf("%d%d", &id, &newval);
            assert(newval >= 0);
            --id;
            //printf("vert %d is changed ot %d\n", ref[id], newval);
            change(id, newval);
        } else if (s[0] == 'D') {
            break;
        }
    }
}
 
int main() {
#if __APPLE__
    freopen("QTREE.in", "r", stdin);
    freopen("QTREE.out", "w", stdout);
#endif
 
    int t;
    scanf("%d", &t);
 
    for (int i = 0; i < t; i++) {
        solve();
    }
}
