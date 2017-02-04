#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double pi = acos(-1);

struct Node {
    Node *l, *r;
    ll y, V, mx, ans;
    Node() {}
    Node(ll V, ll mx) : l(nullptr), r(nullptr), y(rand()), V(V), mx(mx), ans(mx) {}
};

ll getmx(Node *node) {
    return node ? node->ans : 0;
}

void relax(Node *node) {
    if (!node) return;
    node->ans = max(node->mx, max(getmx(node->l), getmx(node->r)));
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

void split(Node *node, ll x, Node *&left, Node *&right) {
    if (!node) {
        left = right = nullptr;
        return;
    }

    if (x < node->V) {
        split(node->l, x, left, node->l);
        right = node;
        relax(right);
    } else {
        split(node->r, x, node->r, right);
        left = node;
        relax(left);
    }
}

void insert(Node *&root, ll V, ll dp) {
    Node *A, *B;
    Node *node = new Node(V, dp);
    split(root, V, A, B);
    root = merge(A, node);
    root = merge(root, B);
}

ll get(Node *&root, ll V) {
    Node *A, *B;
    split(root, V - 1, A, B);
    ll ret = getmx(A);
    root = merge(A, B);
    return ret + V;
}

int main() {
    srand(time(NULL));

    int n;
    scanf("%d", &n);

    Node *root = nullptr;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll r, h;
        cin >> r >> h;
        ll V = r * r * h;
        ll dp = get(root, V);
        insert(root, V, dp);
        ans = max(ans, dp);
    }

    printf("%.10lf\n", ans * pi);
}

