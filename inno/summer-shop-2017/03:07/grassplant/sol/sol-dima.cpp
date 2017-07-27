#include <bits/stdc++.h>
using namespace std;

struct Node {
    int L, R;
    Node* l;
    Node* r;
    int sum, bl;

    Node() {
    }
    
    Node(int L, int R) : L(L), R(R), l(nullptr), r(nullptr), sum(0), bl(0) {
    }

    Node(Node* l, Node* r) : L(l->L), R(r->R), l(l), r(r), sum(l->sum + r->sum), bl(0) {
    }
};

Node* buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void add(Node* node, int val) {
    if (!node) return;
    node->sum += val;
    node->bl += val;
}

void push(Node* node) {
    if (!node) return;
    add(node->l, node->bl);
    add(node->r, node->bl);
    node->bl = 0;
}

void add(Node* node, int L, int R, int val) {
    if (node->R <= L || R <= node->L) return;
    if (L <= node->L && node->R <= R) {
        add(node, val);
        return;
    }
    push(node);
    add(node->l, L, R, val);
    add(node->r, L, R, val);
    node->sum = node->l->sum + node->r->sum;
}

int get(Node* node, int pos) {
    if (node->R - node->L == 1) return node->sum;
    push(node);
    if (pos < node->l->R) return get(node->l, pos);
    return get(node->r, pos);
}

const int N = 1e5;
const int K = 18;

vector<int> g[N];
int sz[N], up[K][N], tin[N], tout[N];

int T = 0;

void dfs(int v, int p) {
    tin[v] = T++;
    up[0][v] = p;
    for (int i = 1; i < K; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sz[v] += sz[u];
        }
    }
    tout[v] = T++;
}

int sa[N], no[N], sz_comp[N], batya[N];
int num = 0;
vector<Node*> trees;

void go(int v, int p) {
    if (v == p || 2 * sz[v] <= sz[p]) {
        sa[v] = num++;
        batya[sa[v]] = v;
        no[v] = 0;
    } else {
        sa[v] = sa[p];
        no[v] = no[p] + 1;
    }
    ++sz_comp[sa[v]];

    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
}

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int get_lca(int v, int u) {
    for (int i = K - 1; i >= 0; --i) {
        if (!is_anc(up[i][u], v)) {
            u = up[i][u];
        }
    }
    return is_anc(u, v) ? u : up[0][u];
}

void add_up(int v, int lca, int val) {
    while (sa[v] != sa[lca]) {
        add(trees[sa[v]], 0, no[v] + 1, 1);
        v = up[0][batya[sa[v]]];
    }
    add(trees[sa[v]], no[lca] + 1, no[v] + 1, 1);
}

void add_on_path(int v, int u, int val) {
    int lca = get_lca(v, u);
    add_up(v, lca, val);
    add_up(u, lca, val);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);
    go(0, 0);

    trees.resize(num);
    for (int i = 0; i < num; ++i) {
        trees[i] = buildTree(0, sz_comp[i]);
    }

    for (int i = 0; i < m; ++i) {
        char c;
        int a, b;
        scanf(" %c%d%d", &c, &a, &b);
        --a, --b;

        if (c == 'P') {
            add_on_path(a, b, 1);
        } else {
            if (is_anc(b, a)) swap(a, b);
            printf("%d\n", get(trees[sa[b]], no[b]));
        }
    }
}
