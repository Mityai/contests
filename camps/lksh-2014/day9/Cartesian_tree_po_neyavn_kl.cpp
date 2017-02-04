#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

typedef long long ll;

using namespace std;


const int MAXN = 100000;

struct TNode {
    int y, x;
    int left, right;

    int w;
};

int root = -1;
TNode tree[MAXN];

int getW(int node) {
    if (node == -1) {
        return 0;
    }

    return tree[node].w;
}

void relax(int node) {
    if (node == -1) {
        return;
    }

    tree[node].w = 1 + getW(tree[node].left) + getW(tree[node].right);
}

void split(int node, int k, int &left, int &right) {
    if (node == -1) {
        left = right = -1;
        return;
    }

    if (getW(tree[node].left) < k) {
        split(tree[node].right, k - getW(tree[node].left) - 1, left, right);
        tree[node].right = left;
        
        relax(tree[node].right);
        relax(node);

        left = node;
    } else {
        split(tree[node].left, k, left, right);
        tree[node].left = right;
        relax(tree[node].left);
        relax(node);

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
        relax(left);

        return left;
    } else {
        tree[right].left = _merge(left, tree[right].left);
        
        relax(tree[right].left);
        relax(right);

        return right;
    }
}

int tc = 0;

int newNode(int x) {
    tree[tc].x = x;
    tree[tc].y = rand();
    tree[tc].left = -1;
    tree[tc].right = -1;

    return tc++;
}

void _insert(int node) {
    int left = -1, right = -1;
    split(root, tree[node].x, left, right);

    left = _merge(left, node);
    relax(left);

    root = _merge(left, right);
    relax(root);
}

void moveToFront(int l, int r) {
    int A = -1, B = -1, C = -1, temp = -1;
    split(root, l, A, temp);

    split(temp, r - l + 1, B, C);

    B = _merge(B, A);
    relax(B);

    root = _merge(B, C);
    relax(root);
}

void print(int node) {
    if (node == -1) {
        return;
    }

    print(tree[node].left);
    printf("%d ", tree[node].x);
    print(tree[node].right);
}

int main() {
    freopen("movetofront.in", "r", stdin);
    freopen("movetofront.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        _insert(newNode(i));
    }

    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        moveToFront(l - 1, r - 1);
    }

    print(root);
}
