#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    Node *left, *right;
    ll x, sum, w, y;
    
    Node() : left(nullptr), right(nullptr) {};
    Node(ll x) : left(nullptr), right(nullptr), x(x) {
        sum = x;
        w = 1;
        y = rand();
    }
};

Node *rootOdd = nullptr;
Node *rootEven = nullptr;

ll getW(Node *node) {
    if (!node) return 0;
    return node->w;
}

ll getSum(Node *node) {
    if (!node) return 0;
    return node->sum;
}

void relax(Node *node) {
    if (!node) return;
    node->w = 1 + getW(node->left) + getW(node->right);
    node->sum = node->x + getSum(node->left) + getSum(node->right);
}

void split(Node *node, ll k, Node *&left, Node *&right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    
    if (getW(node->left) < k) {
        split(node->right, k - getW(node->left) - 1, node->right, right);
        left = node;
        relax(left);
    } else {
        split(node->left, k, left, node->left);
        right = node;
        relax(right);
    }
}

Node *_merge(Node *left, Node *right) {
    if (!left) return right;
    if (!right) return left;
    
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

void _insert(int pos, ll x, bool odd) {
    Node *&root = (odd ? rootOdd : rootEven);
    Node *A, *B;
    split(root, pos, A, B);
    root = _merge(A, new Node(x));
    root = _merge(root, B);
}

ll getSum(int l, int r, bool odd) {
    Node *root = (odd ? rootOdd : rootEven);
    Node *A, *B, *C;
    split(root, (r + odd) / 2, B, C);
    split(B, (l + odd) / 2, A, B);
    
    ll res = getSum(B);
    root = _merge(A, B);
    root = _merge(root, C);
    return res;
}

void swap_tree(int l, int r) {
    Node *Aodd, *Bodd, *Codd;
    Node *Aeven, *Beven, *Ceven;
    
    split(rootOdd, (r + 1) / 2, Bodd, Codd);
    split(Bodd, (l + 1) / 2, Aodd, Bodd);
    split(rootEven, r / 2, Beven, Ceven);
    split(Beven, l / 2, Aeven, Beven);
    
    rootOdd = _merge(Aodd, Beven);
    rootOdd = _merge(rootOdd, Codd);
    rootEven = _merge(Aeven, Bodd);
    rootEven = _merge(rootEven, Ceven);
}

void print(Node *node) {
    if (!node) return;
    print(node->left);
    cout << node->x << ' ';
    print(node->right);
}

// 1 2 3 4 5
// 1 3 2 5 4
// 3 1 5 2 4
// 1 3 5
// 2 4

int main() {
#if __APPLE__
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#else
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#endif
    
    for (int i = 1;; i++) {
        int n, m;
        scanf("%d%d", &n, &m);
        
        if (n == 0 && m == 0) return 0;
    
        for (int i = 0; i < n; i++) {
            ll x;
            scanf("%lld", &x);
        
            _insert(i / 2, x, 1 - i % 2);
        }
    
        cout << "Swapper " << i << ":" << endl;
        for (int i = 0; i < m; i++) {
            int type, a, b;
            scanf("%d%d%d", &type, &a, &b);
        
            --a;
        
            if (type == 1) {
                swap_tree(a, b);
            } else {
                cout << getSum(a, b, false) + getSum(a, b, true) << endl;
            }
        }
    }
}
