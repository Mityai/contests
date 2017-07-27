#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1e9;

struct Node {
    int L;
    int R;
    Node* l;
    Node* r;
    int minv;
    int maxv;

    Node() {}

    Node(int L, int R) : L(L), R(R), l(nullptr), r(nullptr), minv(0), maxv(0) {
    }

    Node(Node* l, Node* r) : L(l->L), R(r->R), l(l), r(r), minv(0), maxv(0) {
    }
};

Node* buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void setval(Node* node, int minv, int maxv) {
    if (!node) return;
    if (node->minv > maxv) {
        node->minv = node->maxv = maxv;
    } else if (node->maxv < minv) {
        node->minv = node->maxv = minv;
    } else {
        node->minv = max(node->minv, minv);
        node->maxv = min(node->maxv, maxv);
    }
}

void push(Node* node) {
    if (!node) return;
    setval(node->l, node->minv, node->maxv);
    setval(node->r, node->minv, node->maxv);
    node->minv = 0;
    node->maxv = INF;
}

void setval(Node* node, int L, int R, int minv, int maxv) {
    if (node->R <= L || R <= node->L) return;
    if (L <= node->L && node->R <= R) {
        setval(node, minv, maxv);
        return;
    }
    push(node);
    setval(node->l, L, R, minv, maxv);
    setval(node->r, L, R, minv, maxv);
}

int get(Node* node, int pos) {
    if (node->R - node->L == 1) {
        return node->minv;
    }
    push(node);
    if (pos < node->l->R) return get(node->l, pos);
    return get(node->r, pos);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    Node* root = buildTree(0, n);

    for (int i = 0; i < k; ++i) {
        int t, l, r, x;
        scanf("%d%d%d%d", &t, &l, &r, &x);

        if (t == 1) {
            setval(root, l, r + 1, x, INF);
        } else {
            setval(root, l, r + 1, 0, x);
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\n", get(root, i));
    }
}
