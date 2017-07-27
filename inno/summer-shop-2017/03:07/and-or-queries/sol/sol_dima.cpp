#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

const int N = 2e5;

int a[N], l[N], r[N], x[N];

struct Node {
    Node* l;
    Node* r;
    int mn, bl;

    Node() {
    }

    Node(int L, int R, int i) : l(nullptr), r(nullptr), mn((a[L] >> i) & 1), bl(0) {
    }

    Node(Node* l, Node* r) : l(l), r(r), mn(min(l->mn, r->mn)), bl(0) {
    }
};

Node* buildTree(int L, int R, int i) {
    if (R - L == 1) return new Node(L, R, i);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M, i), buildTree(M, R, i));
}

void add(Node* node, int val) {
    if (!node) return;
    node->mn += val;
    node->bl += val;
}

void push(Node* node) {
    if (!node) return;
    add(node->l, node->bl);
    add(node->r, node->bl);
    node->bl = 0;
}

void add(Node* node, int L, int R, int l, int r, int val) {
    if (r <= L || R <= l) return;
    if (L <= l && r <= R) {
        add(node, val);
        return;
    }
    push(node);
    int m = (l + r) / 2;
    add(node->l, L, R, l, m, val);
    add(node->r, L, R, m, r, val);
    node->mn = min(node->l->mn, node->r->mn);
}

int getmin(Node* node, int L, int R, int l, int r) {
    if (r <= L || R <= L) return INF;
    if (L <= l && r <= R) return node->mn;
    push(node);
    int m = (l + r) / 2;
    return min(getmin(node->l, L, R, l, m), getmin(node->r, L, R, m, r));
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<Node*> bits(30);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        for (int j = 0; j < 30; ++j) {
            a[i] ^= 1 << j;
        }
    }

    for (int i = 0; i < 30; ++i) {
        bits[i] = buildTree(0, n, i);
    }

    for (int i = 0; i < m; ++i) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            scanf("%d%d%d", &l[i], &r[i], &x[i]);
            --l[i];
            for (int j = 0; j < 30; ++j) {
                if (((x[i] >> j) & 1) == 0) {
                    add(bits[j], l[i], r[i], 0, n, 1);
                }
            }
        } else if (t == 2) {
            scanf("%d%d", &l[i], &r[i]);
            --l[i];
            int ans = 0;
            for (int j = 0; j < 30; ++j) {
                if (getmin(bits[j], l[i], r[i], 0, n) == 0) {
                    ans |= (1 << j);
                }
            }
            printf("%d\n", ans);
        } else {
            int k;
            scanf("%d", &k);
            --k;
            for (int j = 0; j < 30; ++j) {
                if (((x[k] >> j) & 1) == 0) {
                    add(bits[j], l[k], r[k], 0, n, -1);
                }
            }
        }
    }
}
