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

    int key;
    ll key_mega;
};

const int MAXN = 100000 + 1;

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
        return root;
    }

    int M = (L + R) / 2;
    int left = tree[root].left = buildTree(L, M);
    int right = tree[root].right = buildTree(M, R);

    return root;
}

int getSumInv(int node, int L, int R) {
    if (tree[node].L >= R || tree[node].R <= L) {
        return 0;
    }

    if (L <= tree[node].L && tree[node].R <= R) {
        return tree[node].key;
    }

    return getSumInv(tree[node].left, L, R) + getSumInv(tree[node].right, L, R);
}

ll getSumMegaInv(int node, int L, int R) {
    if (tree[node].L >= R || tree[node].R <= L) {
        return 0;
    }

    if (L <= tree[node].L && tree[node].R <= R) {
        return tree[node].key_mega;
    }

    return getSumMegaInv(tree[node].left, L, R) + getSumMegaInv(tree[node].right, L, R);
}


void update(int node, int pos, int x) {
    if (pos < tree[node].L || tree[node].R <= pos) {
        return;
    }

    if (tree[node].R - tree[node].L == 1) {
        tree[node].key = x;
        return;
    }

    int left = tree[node].left;
    int right = tree[node].right;

    update(left, pos, x);
    update(right, pos, x);

    tree[node].key = tree[left].key + tree[right].key;
}

void update_mega(int node, int pos, ll x) {
    if (pos < tree[node].L || tree[node].R <= pos) {
        return;
    }

    if (tree[node].R - tree[node].L == 1) {
        tree[node].key_mega = x;
        return;
    }

    int left = tree[node].left;
    int right = tree[node].right;

    update_mega(left, pos, x);
    update_mega(right, pos, x);

    tree[node].key_mega = tree[left].key_mega + tree[right].key_mega;
}

int a[MAXN];

int main() {
    freopen("mega.in", "r", stdin);
    freopen("mega.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        --a[i];
    }

    int root = buildTree(0, n);


    ll ans_inver = 0, ans_megainver = 0;
    for (int i = 0; i < n; i++) {
        update(root, a[i], 1);
        int sum = getSumInv(root, a[i] + 1, n);
        ans_inver += ll(sum);
        
        update_mega(root, a[i], ll(sum));
        ans_megainver += getSumMegaInv(root, a[i] + 1, n);
    }

    printf("%lld\n", ans_megainver);
}