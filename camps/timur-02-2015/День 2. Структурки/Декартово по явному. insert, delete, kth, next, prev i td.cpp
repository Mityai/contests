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

void _split(TNode *node, int key, TNode *&left, TNode *&right) {
    if (node == NULL) {
        left = right = NULL;
        return;
    }

    if (key < node->key) {
        _split(node->left, key, left, node->left);
        right = node;
        relax(right);
    } else {
        _split(node->right, key, node->right, right);
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

int mostLeft(TNode *node) {
    int res;
    while (node != NULL) {
        res = node->key;
        node = node->left;
    }
    return res;
}

int mostRight(TNode *node) {
    int res;
    while (node != NULL) {
        res = node->key;
        node = node->right;
    }
    return res;
}

bool _exists(TNode *node, int x) {
    if (node == NULL) return false;
    if (node->key == x) return true;
    if (node->key > x) return _exists(node->left, x);
    if (node->key < x) return _exists(node->right, x);
}

void _insert(int x) {
    if (_exists(root, x)) return;
    TNode *node = new TNode(x);
    TNode *A, *B;
    _split(root, x, A, B);
    root = _merge(A, node);
    root = _merge(root, B);
}

void _delete(int x) {
    if (!_exists(root, x)) return;
    TNode *A, *B, *trash;
    _split(root, x - 1, A, B);
    _split(B, x, trash, B);
    root = _merge(A, B);
}

int _next(int x) {
    TNode *A, *B;
    _split(root, x, A, B);

    int ret;
    if (B == NULL) ret = -1;
    else ret = mostLeft(B);

    root = _merge(A, B);

    return ret;
}

int _prev(int x) {
    TNode *A, *B;
    _split(root, x - 1, A, B);

    int ret;
    if (A == NULL) ret = -1;
    else ret = mostRight(A);

    root = _merge(A, B);

    return ret;
}

int find_kth(TNode *node, int k) {
    if (getW(node->left) + 1 == k) {
        return node->key;
    }

    if (getW(node->left) >= k) {
        find_kth(node->left, k);
    } else {
        find_kth(node->right, k - getW(node->left) - 1);
    }
}

int _kth(int k) {
    if (root == NULL) return -1;
    if (root->w < k) return -1;
    return find_kth(root, k);
}

void print(int val) {
    if (val == -1) {
        printf("none\n");
        return;
    }

    printf("%d\n", val);
}

void print(bool val) {
    if (val) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string req;
    while (cin >> req) {
        int x;
        cin >> x;

        if (req == "insert") {
            _insert(x);
        } else if (req == "delete") {
            _delete(x);
        } else if (req == "exists") {
            print(_exists(root, x));
        } else if (req == "next") {
            print(_next(x));
        } else if (req == "prev") {
            print(_prev(x));
        } else if (req == "kth") {
            print(_kth(x));
        }
    }
}
