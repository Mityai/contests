#include <bits/stdc++.h>

#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;

const int INF = 1234657890;
const int MAXN = 1e5;
const ll MOD1 = 12345;
const ll MOD2 = 23456;

struct TNode {
    int key, y, w;
    TNode *left, *right;

    TNode() {}
    TNode(int key) : key(key) {
        y = rand();
        left = NULL;
        right = NULL;
        w = 1;
    }
};

TNode *root = NULL;

int getW(TNode *node) {
    if (node == NULL) return 0;
    return node->w;
}

void relax(TNode *node) {
    if (node == NULL) return;
    node->w = getW(node->left) + getW(node->right) + 1;
}

void _split(TNode *node, int k, TNode *&left, TNode *&right) {
    if (node == NULL) {
        left = right = NULL;
        return;
    }

    if (getW(node->left) >= k) {
        _split(node->left, k, left, node->left);
        right = node;
        relax(right);
    } else {
        _split(node->right, k - getW(node->left) - 1, node->right, right);
        left = node;
        relax(left);
    }
}

TNode *_merge(TNode *left, TNode *right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (left->y > right->y) {
        left->right = _merge(left->right, right);
        relax(left);
        return left;
    } else {
        right->left = _merge(left, right->left);
        relax(right);
        return right;
    }
}


void _insert(int x) {
    TNode *node = new TNode(x);
    root = _merge(root, node);
}

void moveToFront(int l, int r) {
    TNode *A, *B, *C;
    _split(root, r, A, C);
    _split(A, l - 1, A, B);
    root = _merge(B, A);
    root = _merge(root, C);
}

void print(TNode *node) {
    if (node == NULL) return;
    print(node->left);
    printf("%d ", node->key);
    print(node->right);
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        _insert(i);
    }

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;

        moveToFront(l, r);
    }

    print(root);
}
