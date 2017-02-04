#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    Node *l, *r;
    int y, x, w;
    int prev, mx;

    Node() : l(nullptr), r(nullptr), y(rand()), w(1), prev(0), mx(0) {}
    Node(int x) : Node() {
        this->x = x;
    }
};

int getW(Node *node) {
    if (!node) return 0;
    return node->w;
}

int getMX(Node *node) {
    if (!node) return 0;
    return node->mx;
}

void relax(Node *node) {
    if (!node) return;
    node->w = 1 + getW(node->l) + getW(node->r);
    node->mx = max(node->prev, max(getMX(node->l), getMX(node->r)));
}

Node *merge(Node *left, Node *right) {
    if (!left) return right;
    if (!right) return left;

    if (left->y > right->y) {
        left->r = merge(left->r, right);
        relax(left);
        return left;
    } else {
        right->l = merge(left, right->l);
        relax(right);
        return right;
    }
}

void split(Node *node, int x, Node *&left, Node *&right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (node->x <= x) {
        split(node->r, x, node->r, right);
        left = node;
        relax(left);
    } else {
        split(node->l, x, left, node->l);
        right = node;
        relax(right);
    }
}

void splitK(Node *node, int k, Node *&left, Node *&right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    
    if (getW(node->l) + 1 <= k) {
        splitK(node->r, k - getW(node->l) - 1, node->r, right);
        left = node;
        relax(left);
    } else {
        splitK(node->l, k, left, node->l);
        right = node;
        relax(right);
    }
}

bool find(Node *&root, int x) {
    Node *A, *B, *C;
    split(root, x, A, C);
    split(A, x - 1, A, B);
    bool ok = (B != nullptr);
    root = merge(A, B);
    root = merge(root, C);
    return ok;
}

Node *getright(Node *node) {
    if (!node) return nullptr;
    if (node->r) return getright(node->r);
    return node;
}

Node *getleft(Node *node) {
    if (!node) return nullptr;
    if (node->l) return getleft(node->l);
    return node;
}

void insert(Node *&root, Node *node) {
    Node *A, *B;
    split(root, node->x, A, B);
    Node *rightnode;
    splitK(A, getW(A) - 1, A, rightnode);
    Node *leftnode;
    splitK(B, 1, leftnode, B);
    if (rightnode) {
        node->prev = node->x - rightnode->x - 1;
        relax(node);
    }
    if (leftnode) {
        leftnode->prev = leftnode->x - node->x - 1;
        relax(leftnode);
    }
    A = merge(A, rightnode);
    B = merge(leftnode, B);
    root = merge(A, node);
    root = merge(root, B);
}

void erase(Node *&root, int x) {
    Node *A, *B, *C;
    split(root, x, A, C);
    split(A, x - 1, A, B);
    Node *rightnode = getright(A);
    Node *leftnode;
    splitK(C, 1, leftnode, C);
    if (leftnode && rightnode) {
        leftnode->prev = leftnode->x - rightnode->x - 1;
        relax(leftnode);
    }
    C = merge(leftnode, C);
    root = merge(A, C);
}

int get(Node *&root, int L, int R) {
    Node *A, *node, *B;
    split(root, L - 1, A, node);
    split(node, R, node, B);
    Node *mxleft, *mxright;
    splitK(node, 1, mxleft, node);

    int ret = 0;
    if (!mxleft) {
        root = merge(A, node);
        root = merge(root, B);
        return R - L + 1;
    }

    ret = mxleft->x - L;
    if (node) {
        ret = max(ret, node->mx);
    }

    mxright = getright(node);
    if (mxright) {
        ret = max(ret, R - mxright->x);
    } else {
        ret = max(ret, R - mxleft->x);
    }

    root = merge(A, mxleft);
    root = merge(root, node);
    root = merge(root, B);
    return ret;
}

int main() {
    freopen("crystal.in", "r", stdin);
    freopen("crystal.out", "w", stdout);

    srand(time(NULL));

    int n;
    scanf("%d", &n);

    Node *root = nullptr;
    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);

        if (c == 'A') {
            int x;
            scanf("%d", &x);

            if (find(root, x)) {
                erase(root, x);
            } else {
                insert(root, new Node(x));
            }
        } else {
            int L, R;
            scanf("%d%d", &L, &R);
            printf("%d\n", get(root, L, R));
        }
    }
}
