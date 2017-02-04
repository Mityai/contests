#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>

#define sqr(x) x * x

typedef long long ll;

using namespace std;

struct TNode {
    int L, R;
    int left, right;

    int key, val;
};

const int MAXN = 100000;

int n;
int a[MAXN];
TNode tree[2 * MAXN];

int tc = 0;

int newNode(int L, int R) {
    tree[tc].L = L;
    tree[tc].R = R;
    tree[tc].val = -1;

    return tc++;
}

int buildTree(int L, int R) {
    int root = newNode(L, R);

    if (R - L == 1) {
        tree[root].key = a[L];

        return root;
    }

    int M = (L + R) / 2;
    tree[root].left = buildTree(L, M);
    tree[root].right = buildTree(M, R);

    return root;
}

void setVal(int node, int val) {
    if (tree[node].val == -1) {
        tree[node].val = val;
    } else {
        tree[node].val += val;
    }
    tree[node].key += val;
}

void push(int node) {
    if (tree[node].val != -1) {
        if (tree[node].left) {
            setVal(tree[node].left, tree[node].val);
        }

        if (tree[node].right) {
            setVal(tree[node].right, tree[node].val);
        }
        tree[node].val = -1;
    }
}

void segUpdate(int node, int L, int R, int x) {
    if (tree[node].R <= L || tree[node].L >= R) {
        return;
    }

    if (L <= tree[node].L && tree[node].R <= R) {
        setVal(node, x);
        return;
    }

    push(node);

    segUpdate(tree[node].left, L, R, x);
    segUpdate(tree[node].right, L, R, x);
}

int getVal(int node, int pos) {
    int L = tree[node].L;
    int R = tree[node].R;

    push(node);

    if (R - L == 1) {
        return tree[node].key;
    }

    if (pos < tree[tree[node].left].R) {
        return getVal(tree[node].left, pos);
    } else {
        return getVal(tree[node].right, pos);
    }
}

int main() {
    freopen("segment-tree.in", "r", stdin);
    freopen("segment-tree.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }

    buildTree(0, n);

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char c;
        scanf(" %c", &c);

        if (c == 'g') {
            int pos;
            scanf("%d", &pos);

            --pos;

            printf("%d\n", getVal(0, pos));
        }

        if (c == 'a') {
            int l, r, add;
            scanf("%d%d%d", &l, &r, &add);

            segUpdate(0, l - 1, r, add);
        }
    }
}