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

    int key_max, key_min;
};

const int MAXN = 100000;

int n;
TNode tree[2 * MAXN];

int tc = 0;

int newNode(int L, int R) {
    tree[tc].L = L;
    tree[tc].R = R;

    return tc++;
}

int buildTree(int L, int R) {
    int root = newNode(L, R);

    if (R - L == 1) {
        ll k = sqr(ll(L + 1));
        int cur = int(k % 12345 + (k * ll(L + 1)) % 23456);
        tree[root].key_min = cur;
        tree[root].key_max = cur;

        return root;
    }

    int M = (L + R) / 2;
    int left = tree[root].left = buildTree(L, M);
    int right = tree[root].right = buildTree(M, R);

    tree[root].key_min = min(tree[left].key_min, tree[right].key_min);
    tree[root].key_max = max(tree[left].key_max, tree[right].key_max);

    return root;
}

int getMin(int node, int L, int R) {
    if (tree[node].L >= R || tree[node].R <= L) {
        return INT_MAX;
    }

    if (L <= tree[node].L && tree[node].R <= R) {
        return tree[node].key_min;
    }

    return min(getMin(tree[node].left, L, R), getMin(tree[node].right, L, R));
}


int getMax(int node, int L, int R) {
    if (tree[node].L >= R || tree[node].R <= L) {
        return INT_MIN;
    }

    if (L <= tree[node].L && tree[node].R <= R) {
        return tree[node].key_max;
    }

    return max(getMax(tree[node].left, L, R), getMax(tree[node].right, L, R));
}

void update(int node, int pos, int x) {
    if (pos < tree[node].L || tree[node].R <= pos) {
        return;
    }

    if (tree[node].R - tree[node].L == 1) {
        tree[node].key_min = x;
        tree[node].key_max = x;

        return;
    }

    int left = tree[node].left;
    int right = tree[node].right;

    update(left, pos, x);
    update(right, pos, x);

    tree[node].key_min = min(tree[left].key_min, tree[right].key_min);
    tree[node].key_max = max(tree[left].key_max, tree[right].key_max);
}

int main() {
    freopen("rvq.in", "r", stdin);
    freopen("rvq.out", "w", stdout);

    int k;
    scanf("%d", &k);

    buildTree(0, MAXN);

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        if (x > 0) {
            printf("%d\n", getMax(0, x - 1, y) - getMin(0, x - 1, y));
        } else {
            update(0, abs(x) - 1, y);
        }
    }
}