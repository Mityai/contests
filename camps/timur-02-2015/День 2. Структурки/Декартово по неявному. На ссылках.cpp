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
    int key, minkey, y, w;
    TNode *left, *right;

    TNode() {}
    TNode(int key) : key(key), minkey(key) {
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

int getVal(TNode *node) {
    if (node == NULL) return INF;
    return node->minkey;
}

void relax(TNode *node) {
    if (node == NULL) return;
    node->w = getW(node->left) + getW(node->right) + 1;
    node->minkey = min(node->key, min(getVal(node->left), getVal(node->right)));
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


void _insert(int x, int pos) {
    TNode *node = new TNode(x);
    TNode *A, *B;
    _split(root, pos, A, B);
    root = _merge(A, node);
    root = _merge(root, B);
}

int getMin(int l, int r) {
    TNode *A, *B, *C;
    _split(root, r, A, C);
    _split(A, l - 1, A, B);
    int ret = B->minkey;
    root = _merge(A, B);
    root = _merge(root, C);
    return ret;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;

        if (c == '+') {
            int i, x;
            cin >> i >> x;

            _insert(x, i);
        } else {
            int l, r;
            cin >> l >> r;

            printf("%d\n", getMin(l, r));
        }
    }
}
