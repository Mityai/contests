#include <bits/stdc++.h>
using namespace std;

const int N = 5e5;
const int K = 20;
const int F = 6e7;

int a[N];

int nxt[F][2];
int tc = 0;

void add(int v, int y) {
    for (int i = K; i >= 0; i--) {
        int x = ((y >> i) & 1);
        if (nxt[v][x] == 0) nxt[v][x] = ++tc;
        v = nxt[v][x];
    }
}

struct Node {
    Node *l, *r;
    int L, R;
    int bor;

    Node() {}
    Node(int L, int R) : l(nullptr), r(nullptr), L(L), R(R) {
        bor = ++tc;
        for (int i = L; i < R; i++) {
            add(bor, a[i]);
        }
    }
    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        bor = ++tc;
        for (int i = L; i < R; i++) {
            add(bor, a[i]);
        }
    }
};

int getmaxxor(int v, int x) {
    int mx = 0;
    for (int i = K; i >= 0; i--) {
        int cur = ((x >> i) & 1);
        if (nxt[v][1 - cur] != 0) mx |= (1 << i), v = nxt[v][1 - cur];
        else v = nxt[v][cur];
    }
    return mx;
}

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

int getxor(Node *node, int L, int R, int x) {
    if (node->R <= L || R <= node->L) return 0;
    if (L <= node->L && node->R <= R) {
        return getmaxxor(node->bor, x);
    }
    return max(getxor(node->l, L, R, x), getxor(node->r, L, R, x));
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    Node *root = buildTree(0, n);

    for (int i = 0; i < q; i++) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        printf("%d\n", getxor(root, l - 1, r, x));
    }
}
