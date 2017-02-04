#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e5;

int n, k, q;
int a[N];

struct Node {
    Node * l;
    Node * r;
    int L;
    int R;
    vector<int> sum;
    int md;

    Node() : l(nullptr), r(nullptr), md(0) {
    }

    Node(int L, int R) : Node() {
        this->L = L;
        this->R = R;
        sum.resize(k);
        sum[a[L]] = 1;
    }

    Node(Node * l, Node * r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        sum.resize(k);
        for (int i = 0; i < k; ++i) {
            sum[i] = l->sum[i] + r->sum[i];
        }
        md = 0;
    }
};

Node * buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void add(Node * node, int val) {
    if (!node) return;
    vector<int> tmp(k);
    for (int i = 0; i < k; ++i) {
        tmp[(i + val) % k] = node->sum[i];
    }
    node->sum = tmp;
    node->md += val;
}

void push(Node * node) {
    if (node->md != 0) {
        add(node->l, node->md);
        add(node->r, node->md);
        node->md = 0;
    }
}

void add(Node * node, int L, int R, int val) {
    if (node->R <= L || R <= node->L) return;
    if (L <= node->L && node->R <= R) {
        add(node, val);
        return;
    }
    push(node);
    add(node->l, L, R, val);
    add(node->r, L, R, val);
    for (int i = 0; i < k; ++i) {
        node->sum[i] = node->l->sum[i] + node->r->sum[i];
    }
}

int getsum(Node * node, int L, int R) {
    if (node->R <= L || R <= node->L) return 0;
    if (L <= node->L && node->R <= R) {
        int ret = 0;
        for (int i = 0; i < k; ++i) {
            ret += node->sum[i] * i;
        }
        return ret;
    }
    push(node);
    return getsum(node->l, L, R) + getsum(node->r, L, R);
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    scanf("%d%d%d", &n, &k, &q);

    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }

    Node * root = buildTree(0, n);

    for (int i = 0; i < q; ++i) {
        int t, l, r;
        scanf("%d%d%d", &t, &l, &r);
        --l;
        if (t == 0) {
            int d;
            scanf("%d", &d);
            add(root, l, r, d);
        } else {
            printf("%d\n", getsum(root, l, r));
        }
    }
}
