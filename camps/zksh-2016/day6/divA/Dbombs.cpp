#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1234567890;
const int N = 4e5;

vector<int> g[N], gt[N], gnew[N];
int minv[N], maxv[N];
bool mark[N];
int tc = 0;

struct Node {
    Node *l, *r;
    int L, R;
    int num;

    Node() {}
    Node(int L, int R)
        : l(nullptr), r(nullptr), L(L), R(R) {
        num = L;
    }
    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        num = tc++;
        g[num].push_back(l->num);
        g[num].push_back(r->num);
        gt[l->num].push_back(num);
        gt[r->num].push_back(num);
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void addEdge(Node *node, int L, int R, int v) {
    if (node->R <= L || R <= node->L) return;
    if (L <= node->L && node->R <= R) {
        g[v].push_back(node->num);
        gt[node->num].push_back(v);
        return;
    }
    addEdge(node->l, L, R, v);
    addEdge(node->r, L, R, v);
}

struct Bomb {
    ll x, r;
    int i;
};

bool cmpx(Bomb b1, Bomb b2) {
    return b1.x < b2.x;
}

vector<int> tout, comp;

void dfs1(int v) {
    mark[v] = true;
    for (int u : g[v]) {
        if (!mark[u]) {
            dfs1(u);
        }
    }
    tout.push_back(v);
}


void dfs2(int v) {
    mark[v] = true;
    comp.push_back(v);
    for (int u : gt[v]) {
        if (!mark[u]) {
            dfs2(u);
        }
    }
}

void calcans(int v) {
    mark[v] = true;
    for (int u : gnew[v]) {
        if (!mark[u]) {
            calcans(u);
        }
        minv[v] = min(minv[v], minv[u]);
        maxv[v] = max(maxv[v], maxv[u]);
    }
}

void clear(int n) {
    for (int i = 0; i < n; i++) g[i].clear(), gt[i].clear(), gnew[i].clear();
    memset(mark, 0, n * sizeof(mark[0]));
    tout.clear();
    comp.clear();
}

void solve() {
    int n;
    scanf("%d", &n);

    clear(n);

    vector<Bomb> bomb(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", &bomb[i].x, &bomb[i].r);
        bomb[i].i = i;
    }

    tc = n;
    Node *node = buildTree(0, n);

    sort(bomb.begin(), bomb.end(), cmpx);
    for (int i = 0; i < n; i++) {
        int posl, posr;
        {
            int lb = -1, rb = n - 1;
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if (bomb[mb].x < bomb[i].x - bomb[i].r) lb = mb;
                else rb = mb;
            }
            posl = rb;
        }
        {
            int lb = 0, rb = n;
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if (bomb[mb].x <= bomb[i].x + bomb[i].r) lb = mb;
                else rb = mb;
            }
            posr = rb;
        }
        addEdge(node, posl, posr, i);
    }

    for (int i = 0; i < tc; i++) {
        if (!mark[i]) {
            dfs1(i);
        }
    }

    int component[tc];
    int compnum = 0;
    memset(component, -1, tc * sizeof(component[0]));
    memset(mark, 0, tc * sizeof(mark[0]));
    fill(minv, minv + tc, INF);
    fill(maxv, maxv + tc, -INF);
    for (int i = 0; i < tc; i++) {
        int v = tout[tc - i - 1];
        if (!mark[v]) {
            comp.clear();
            dfs2(v);

            for (int u : comp) {
                component[u] = compnum;
                if (0 <= u && u < n) {
                    minv[compnum] = min(minv[compnum], u);
                    maxv[compnum] = max(maxv[compnum], u);
                }
            }
            compnum++;
        }
    }

    for (int v = 0; v < tc; v++) {
        for (int u : g[v]) {
            if (component[v] != component[u]) {
                gnew[component[v]].push_back(component[u]);
            }
        }
    }

    memset(mark, 0, tc * sizeof(mark[0]));
    for (int v = 0; v < tc; v++) {
        if (!mark[v]) {
            calcans(v);
        }
    }

    int ans[n];
    for (int i = 0; i < n; i++) {
        int left = minv[component[i]], right = maxv[component[i]];
        ans[bomb[i].i] = right - left + 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    puts("");

    clear(tc);
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        solve();
    }
}
