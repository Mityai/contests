#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

struct Node {
    Node *l, *r;
    int L, R;
    pair<int, int> mx;
    int ch;

    Node() {
    }

    Node(int L, int R) : l(nullptr), r(nullptr), L(L), R(R), mx({0, -L}), ch(0) {
    }

    Node(Node *l, Node *r) : l(l), r(r), L(l->L), R(r->R), mx(max(l->mx, r->mx)), ch(0) {
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void add(Node *node, int val) {
    if (!node) return;
    node->mx.fi += val;
    node->ch += val;
}

void push(Node *node) {
    add(node->l, node->ch);
    add(node->r, node->ch);
    node->ch = 0;
}

void add(Node *node, int L, int R, int val) {
    if (node->R <= L || R <= node->L) return;
    if (L <= node->L && node->R <= R) {
        add(node, val);
        return;
    }
    push(node);
    add(node->l, L, R, val);
    add(node->r, L, R, val);
    node->mx = max(node->l->mx, node->r->mx);
}

pair<int, int> getmax(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) return make_pair(-1, -1);
    if (L <= node->L && node->R <= R) return node->mx;
    push(node);
    return max(getmax(node->l, L, R), getmax(node->r, L, R));
}

const int N = 1e6;
int cnt[N + 2][3];

int suff2[N + 2];

int main() {
#if __APPLE__
    freopen("J.in", "r", stdin);
    freopen("J.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    set<int> all;
    for (int i = 0; i < n; ++i) {
        int V, C;
        scanf("%d%d", &V, &C);
        ++cnt[V][C];
        all.insert(V);
    }

    for (int i = N; i >= 0; --i) {
        suff2[i] = suff2[i + 1] + cnt[i][2];
    }

    Node * root = buildTree(0, N + 2);

    pair<int, pair<int, int>> ans = {suff2[1] + cnt[0][0], {0, 0}};
    for (int B : all) {
        int cur = suff2[B + 1];
        add(root, B, N + 1, cnt[B][0]);
        if (B != 0) {
            add(root, 0, B, cnt[B][1]);
        }
        auto mx = getmax(root, 0, B + 1);
        cur += mx.fi;
        pair<int, pair<int, int>> here = {cur, {mx.se, B}};
        if (here.fi > ans.fi || (here.fi == ans.fi && -ans.se.fi + ans.se.se > -here.se.fi + here.se.se)) {
            ans = here;
        }
    }

    printf("%d %d\n", -ans.se.fi, ans.se.se);
}
