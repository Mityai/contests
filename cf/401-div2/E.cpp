#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
    Node* l;
    Node* r;
    int y;
    int x;
    ll h, mx;

    Node() : l(nullptr), r(nullptr), y(rng()) {
    }

    Node(int x_, ll h_) : Node() {
        x = x_;
        h = h_;
        mx = h_;
    }
};

ll getH(Node* node) {
    return node ? node->mx : 0;
}

void relax(Node* node) {
    if (!node) return;
    node->mx = max(node->h, max(getH(node->l), getH(node->r)));
}

Node* merge(Node* left, Node* right) {
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

void split(Node* node, int x, Node*& left, Node*& right) {
    if (node == nullptr) {
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

struct Q {
    int a, b, h;
};

void insert(Node*& root, Node* node) {
    Node* A;
    Node* B;
    split(root, node->x, A, B);
    root = merge(A, node);
    root = merge(root, B);
}

ll getmax(Node*& root, int b) {
    Node* A;
    Node* B;
    split(root, b - 1, A, B);
    ll ret = getH(A);
    root = merge(A, B);
    return ret;
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<Q> q(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &q[i].a, &q[i].b, &q[i].h);
    }

    sort(q.begin(), q.end(),
            [](Q& q1, Q& q2) {
                return q1.b > q2.b || (q1.b == q2.b && q1.a > q2.a);
            });

    ll ans = 0;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        Q& cur = q[i];
        ll curh = getmax(root, cur.b) + cur.h;
        insert(root, new Node(cur.a, curh));
        ans = max(ans, curh);
    }

    printf("%lld\n", ans);
}
