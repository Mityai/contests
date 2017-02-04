#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node * l;
    Node * r;
    int y;
    int x;
    int sz;

    Node() : l(nullptr), r(nullptr), y(rand()), sz(1) {
    }

    Node(int x) : Node() {
        this->x = x;
    }
};

int getsize(Node * node) {
    return node ? node->sz : 0;
}

void relax(Node * node) {
    if (!node) return;
    node->sz = 1 + getsize(node->l) + getsize(node->r);
}

Node * merge(Node * left, Node * right) {
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

void split(Node * node, int x, Node *& left, Node *& right) {
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

void insert(Node *& root, int x) {
    Node * A;
    Node * B;
    split(root, x, A, B);
    root = merge(A, new Node(x));
    root = merge(root, B);
}

void erase(Node *& root, int x) {
    Node * A;
    Node * B;
    Node * C;
    split(root, x - 1, A, B);
    split(B, x, B, C);
    root = merge(A, C);
}

int getcnt(Node *& root, int l, int r) {
    Node * A;
    Node * B;
    Node * C;
    split(root, l - 1, A, B);
    split(B, r, B, C);
    int ret = getsize(B);
    root = merge(A, B);
    root = merge(root, C);
    return ret;
}

const int F = 1e4;
using ll = long long;

struct Radio {
    int x, r, f;
};

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<Node *> roots(F + 1);
    vector<Radio> rs(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &rs[i].x, &rs[i].r, &rs[i].f);
        insert(roots[rs[i].f], rs[i].x);
    }

    sort(rs.begin(), rs.end(), [](Radio& r1, Radio& r2) { return r1.r < r2.r; });

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        Radio& cur = rs[i];
        erase(roots[cur.f], cur.x);
        for (int j = cur.f - k; j <= cur.f + k; ++j) {
            if (1 <= j && j <= F) {
                ans += getcnt(roots[j], cur.x - cur.r, cur.x + cur.r);
            }
        }
    }

    printf("%lld\n", ans);
}
