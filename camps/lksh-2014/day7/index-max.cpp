#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>

typedef long long ll;

using namespace std;

struct TNode {
    int L, R;
    int left, right;

    int key, ind;
};

TNode tree[2000000];
int a[1000000];
int n;

int tc = 0;

int newNode(int L, int R) {
    tree[tc].L = L;
    tree[tc].R = R;

    return tc++;
}

int buildTree(int L, int R) {
    int root = newNode(L, R);

    if (R - L == 1) {
        tree[root].key = a[L];
        tree[root].ind = L;

        return root;
    }

    int M = (L + R) / 2;
    int left = tree[root].left = buildTree(L, M);
    int right = tree[root].right = buildTree(M, R);

    if (tree[left].key >= tree[right].key) {
        tree[root].key = tree[left].key;
        tree[root].ind = tree[left].ind;
    } else {
        tree[root].key = tree[right].key;
        tree[root].ind = tree[right].ind;
    }

    return root;
}

int getMaxInd(int node, int L, int R) {
    if (tree[node].R <= L || tree[node].L >= R) {
        return n - 1;
    }

    if (L <= tree[node].L && tree[node].R <= R) {
        return tree[node].ind;
    }

    int left_ind = getMaxInd(tree[node].left, L, R);
    int right_ind = getMaxInd(tree[node].right, L, R);

    if (a[left_ind] >= a[right_ind]) {
        return left_ind;
    }
    return right_ind;
}

int main() {
    freopen("index-max.in", "r", stdin);
    freopen("index-max.out", "w", stdout);

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    a[n++] = INT_MIN;

    buildTree(0, n - 1);

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        printf("%d ", getMaxInd(0, l - 1, r) + 1);
    }
}