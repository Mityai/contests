#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <climits>
#include <algorithm>

typedef long long ll;

using namespace std;

struct TNode {
    int x, y;
    int p, l, r;
    int n;
};

bool cmp_x(TNode t1, TNode t2) {
    return t1.x < t2.x;
}

bool cmp_n(TNode t1, TNode t2) {
    return t1.n < t2.n;
}

struct TNodeSegm {
    int L, R;
    int left, right;

    int key, ind;
};

vector<TNode> tree;
vector<TNodeSegm> treeSegm;

int n;
int tc = 0;
int rootSegm = -1;

int newNode(int L, int R) {
    treeSegm[tc].L = L;
    treeSegm[tc].R = R;

    return tc++;
}

int buildTreeSegm(int L, int R) {
    int root = newNode(L, R);

    if (R - L == 1) {
        treeSegm[root].key = tree[L].y;
        treeSegm[root].ind = L;

        return root;
    }

    int M = (L + R) / 2;
    int left = treeSegm[root].left = buildTreeSegm(L, M);
    int right = treeSegm[root].right = buildTreeSegm(M, R);

    if (treeSegm[left].key <= treeSegm[right].key) {
        treeSegm[root].key = treeSegm[left].key;
        treeSegm[root].ind = treeSegm[left].ind;
    } else {
        treeSegm[root].key = treeSegm[right].key;
        treeSegm[root].ind = treeSegm[right].ind;
    }

    return root;
}

int getMinInd(int node, int L, int R) {
    if (treeSegm[node].R <= L || treeSegm[node].L >= R) {
        return n;
    }

    if (L <= treeSegm[node].L && treeSegm[node].R <= R) {
        return treeSegm[node].ind;
    }

    int left_ind = getMinInd(treeSegm[node].left, L, R);
    int right_ind = getMinInd(treeSegm[node].right, L, R);

    if (tree[left_ind].y < tree[right_ind].y) {
        return left_ind;
    }
    return right_ind;
}

int getN(int node) {
    if (node == -1) {
        return -1;
    }

    return tree[node].n;
}

int getMin(int l, int r) {
    int i = l;
    for (int j = l; j < r; j++) {
        if (tree[j].y < tree[i].y) {
            i = j;
        }
    }

    return i;
}

int buildTree(int L, int R) {
    if (R - L == 0) {
        return -1;
    }

    int root = getMinInd(rootSegm, L, R);
    int left = tree[root].l = buildTree(L, root);
    int right = tree[root].r = buildTree(root + 1, R);

    tree[root].l = getN(left);
    tree[root].r = getN(right);

    if (L == 0 && R == n) {
        tree[root].p = -1;
    }

    if (left != -1) {
        tree[left].p = tree[root].n;
    }

    if (right != -1) {
        tree[right].p = tree[root].n;
    }

    return root;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);

    scanf("%d", &n);

    tree.resize(n + 1);
    treeSegm.resize(2 * n + 1);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &tree[i].x, &tree[i].y);

        tree[i].n = i;
    }

    tree[n].y = 10000000;
    tree[n].x = 10000000;
    tree[n].n = 500000;

    sort(tree.begin(), tree.end(), cmp_x);

    rootSegm = buildTreeSegm(0, n);
    buildTree(0, n);

    sort(tree.begin(), tree.end(), cmp_n);

    printf("YES\n");
    for (int i = 0; i < tree.size() - 1; i++) {
        printf("%d %d %d\n", tree[i].p + 1, tree[i].l + 1, tree[i].r + 1);
    }
}
