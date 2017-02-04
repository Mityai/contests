#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <climits>

typedef long long ll;

using namespace std;

const ll MOD = 1000 * 1000 * 1000;
const int MAXN = 1000000;

struct TNode {
    ll x, y;
    int left, right;
    ll sum;
};

int root = -1;
TNode tree[MAXN];

ll getSumNode(int node) {
    if (node == -1) {
        return 0;
    }

    return tree[node].sum;
}

void relax(int node) {
    if (node == -1) {
        return;
    }

    int left = tree[node].left;
    int right = tree[node].right;

    tree[node].sum = tree[node].x + getSumNode(left) + getSumNode(right);
}

void split(int node, ll c, int &left, int &right) {
    if (node == -1) {
        left = right = -1;
        return;
    }

    if (tree[node].x <= c) {
        split(tree[node].right, c, left, right);

        tree[node].right = left;

        relax(right);
        relax(tree[node].right);

        left = node;
    } else {
        split(tree[node].left, c, left, right);

        tree[node].left = right;

        relax(left);
        relax(tree[node].left);

        right = node;
    }
}

int _merge(int left, int right) {
    if (left == -1) {
        return right;
    }

    if (right == -1) {
        return left;
    }

    if (tree[left].y < tree[right].y) {
        tree[left].right = _merge(tree[left].right, right);
        relax(tree[left].right);
        relax(right);

        return left;
    } else {
        tree[right].left = _merge(left, tree[right].left);
        relax(tree[right].left);
        relax(left);

        return right;
    }
}

void _insert(int node) {
    int left = -1, right = -1;
    split(root, tree[node].x, left, right);
    relax(root);
    relax(left);
    relax(right);

    left = _merge(left, node);
    relax(left);
    relax(node);

    root = _merge(left, right);
    relax(root);
    relax(left);
    relax(right);
}

ll getSum(int L, int R) {
    int A = -1, B = -1, C = -1;
    split(root, L - 1, A, C);
    relax(root);
    relax(A);
    relax(C);

    int temp = C;
    C = -1;
    split(temp, R, C, B);
    relax(temp);
    relax(C);
    relax(B);

    ll res = getSumNode(C);

    temp = _merge(A, C);
    relax(temp);
    relax(A);
    relax(C);

    root = _merge(temp, B);
    relax(root);
    relax(temp);
    relax(B);

    return res;
}

bool _find(int node, ll x) {
    if (node == -1) {
        return false;
    }

    if (tree[node].x < x) {
        if (tree[node].right == -1) {
            return false;
        }

        return _find(tree[node].right, x);
    } else if (tree[node].x > x) {
        if (tree[node].left == -1) {
            return false;
        }

        return _find(tree[node].left, x);
    }

    return true;
}

int tc = 0;

int newNode(ll x) {
    tree[tc].x = x;
    tree[tc].y = rand();
    tree[tc].left = -1;
    tree[tc].right = -1;
    tree[tc].sum = x;

    return tc++;
}

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);

    int n;
    scanf("%d", &n);

    ll last_y = 0;
    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '+') {
            ll x;
            scanf("%lld", &x);

            if (last_y != 0) {
                x = (x + last_y) % MOD;
            }

            if (!_find(root, x)) {
                int node = newNode(x);
                _insert(node);
            }

            last_y = 0;
        }

        if (c == '?') {
            int l, r;
            scanf("%d%d", &l, &r);

            printf("%lld\n", last_y = getSum(l, r));
        }
    }
}