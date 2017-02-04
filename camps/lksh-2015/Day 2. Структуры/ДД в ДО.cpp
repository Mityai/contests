#include <bits/stdc++.h>
using namespace std;

const int N = int(1e5);

int a[N];

struct TreapNode {
    TreapNode *l, *r;
    int x, y, w;

    TreapNode() : l(nullptr), r(nullptr), x(0), y(rand()), w(1) {}
    TreapNode(int x) : TreapNode() {
        this->x = x;
    }
};

int getSize(TreapNode *node) {
    return node ? node->w : 0;
}

void relax(TreapNode *node) {
    if (!node) return;
    node->w = 1 + getSize(node->l) + getSize(node->r);
}

TreapNode *merge(TreapNode *left, TreapNode *right) {
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

void split(TreapNode *node, int x, TreapNode *&left, TreapNode *&right) {
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

void splitK(TreapNode *node, int k, TreapNode *&left, TreapNode *&right) {
    if (!node) {
        left = right = nullptr;
        return;
    }

    if (getSize(node->l) + 1 <= k) {
        splitK(node->r, k - getSize(node->l) - 1, node->r, right);
        left = node;
        relax(left);
    } else {
        splitK(node->l, k, left, node->l);
        right = node;
        relax(right);
    }
}

void insert(TreapNode *&root, int val) {
    TreapNode *node = new TreapNode(val);
    TreapNode *A, *B;
    split(root, val, A, B);
    root = merge(A, node);
    root = merge(root, B);
}

TreapNode *buildTreap(int L, int R) {
    TreapNode *node = nullptr;
    for (int i = L; i < R; i++) {
        insert(node, a[i]);
    }
    return node;
}

void print(TreapNode *node) {
    if (!node) return;
    print(node->l);
    cout << node->x << ' ';
    print(node->r);
}

struct Node {
    Node *l, *r;
    TreapNode *treap;
    int L, R;

    Node() : l(nullptr), r(nullptr), treap(nullptr), L(0), R(0) {}
    
    Node(int L, int R) : Node() {
        this->L = L;
        this->R = R;
        insert(treap, a[L]);
    }

    Node(Node *l, Node *r) : Node() {
        this->l = l;
        this->r = r;
        L = l->L;
        R = r->R;
        treap = buildTreap(L, R);
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) >> 1;
    return new Node(buildTree(L, M), buildTree(M, R));
}

int getCntLess(TreapNode *&node, int k) {
    TreapNode *A, *B;
    split(node, k, A, B);
    int ret = getSize(A);
    node = merge(A, B);
    return ret;
}

int getCnt(Node *node, int L, int R, int k, int l) {
    if (node->R <= L || R <= node->L) {
        return 0;
    }

    if (L <= node->L && node->R <= R) {
        return getCntLess(node->treap, l) - getCntLess(node->treap, k - 1);
    }

    return getCnt(node->l, L, R, k, l) + getCnt(node->r, L, R, k, l);
}

void change(TreapNode *&node, int from, int to) {
    TreapNode *A, *B, *C;
    split(node, from, A, C);
    splitK(A, getSize(A) - 1, A, B);
    node = merge(A, C);
    insert(node, to);
}

int setVal(Node *&node, int pos, int val) {
    if (node->R - node->L == 1) {
        int tochange = node->treap->x;
        node->treap->x = val;
        return tochange;
    }

    int tochange;
    if (pos < node->l->R) {
        tochange = setVal(node->l, pos, val);
    } else {
        tochange = setVal(node->r, pos, val);
    }
    change(node->treap, tochange, val);
    return tochange;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("permutation2.in", "r", stdin);
    freopen("permutation2.out", "w", stdout);
#endif

    srand(time(NULL));

    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    Node *root = buildTree(0, n);

    for (int i = 0; i < m; i++) {
        char s, s1, s2;
        scanf(" %c", &s);
        scanf("%c%c", &s1, &s2);

        if (s == 'G') {
            int x, y, k, l;
            scanf("%d%d%d%d", &x, &y, &k, &l);
            printf("%d\n", getCnt(root, x - 1, y, k, l));
        } else {
            int pos, val;
            scanf("%d%d", &pos, &val);
            setVal(root, pos - 1, val);
        }
    }
}
