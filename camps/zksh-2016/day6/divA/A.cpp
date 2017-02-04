#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

struct Node {
    Node *l, *r;
    int L, R;
    ll sumA, sumB, sumC;
    ll addA, addB, addC;

    Node() : l(nullptr), r(nullptr) {}
    Node(int L, int R) : l(nullptr), r(nullptr), L(L), R(R) {
        sumA = sumB = sumC = 0;
        addA = addB = addC = 0;
    }
    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        sumA = sumB = sumC = 0;
        addA = addB = addC = 0;
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void addVal(Node *node, ll val, int c) {
    if (!node) return;
    if (c == 1) {
        node->sumA = (node->sumA + (node->R - node->L) * val) % MOD;
        node->addA = (node->addA + val) % MOD;
        node->sumC = (node->sumC + node->sumB * val) % MOD;
    } else {
        node->sumB = (node->sumB + (node->R - node->L) * val) % MOD;
        node->addB = (node->addB + val) % MOD;
        node->sumC = (node->sumC + node->sumA * val) % MOD;
    }
}

void push(Node *node) {
    if (!node) return;
    if (node->addA || node->addB) {
        addVal(node->l, node->addA, 1);
        addVal(node->l, node->addB, 2);
        addVal(node->r, node->addA, 1);
        addVal(node->r, node->addB, 2);
        node->addA = node->addB = 0;
    }
}

void add(Node *node, int L, int R, ll val, int c) {
    if (node->R <= L || R <= node->L) return;
    if (L <= node->L && node->R <= R) {
        addVal(node, val, c);
        return;
    }
    push(node);
    add(node->l, L, R, val, c);
    add(node->r, L, R, val, c);
    node->sumA = (node->l->sumA + node->r->sumA) % MOD;
    node->sumB = (node->l->sumB + node->r->sumB) % MOD;
    node->sumC = (node->l->sumC + node->r->sumC) % MOD;
}

ll getsum(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) return 0;
    if (L <= node->L && node->R <= R) return node->sumC;
    push(node);
    return (getsum(node->l, L, R) + getsum(node->r, L, R)) % MOD;
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    Node *root = buildTree(0, n);
    for (int i = 0; i < m; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '*') {
            int l, r;
            ll x;
            scanf("%d%d%lld", &l, &r, &x);
            --l;
            add(root, l, r, x, 1);
        }
        if (c == '.') {
            int l, r;
            ll x;
            scanf("%d%d%lld", &l, &r, &x);
            --l;
            add(root, l, r, x, 2);
        }
        if (c == '?') {
            int l, r;
            scanf("%d%d", &l, &r);
            --l;
            printf("%lld\n", getsum(root, l, r));
        }
    }
}
