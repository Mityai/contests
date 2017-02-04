#include <iostream>
#include <cstdio>
#include <cstdlib>

typedef long long ll;

using namespace std;

struct TNode {
    int L, R;

    int key;
};

TNode tree[1000000];
int a[30000];

void buildTree(int root, int L, int R) {
    tree[root].L = L;
    tree[root].R = R;

    if (R - L == 1) {
        tree[root].key = a[L];

        return;
    }

    int M = (L + R) / 2;
    buildTree(2 * root, L, M);
    buildTree(2 * root + 1, M, R);

    tree[root].key = min(tree[2 * root].key, tree[2 * root + 1].key);
}

int main() {
    freopen("build-tree.in", "r", stdin);
    freopen("build-tree.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    buildTree(1, 0, n);
    
    printf("%d\n", 2 * n - 1);
    int cnt = 0, i = 0;
    while (cnt < 2 * n - 1) {
        ++i;
        if (tree[i].L == 0 && tree[i].R == 0) {
            continue;
        }

        printf("%d %d %d %d ", i, tree[i].L, tree[i].R, tree[i].key);
        if (tree[i].R - tree[i].L == 1) {
            printf("%d %d\n", -1, -1);
        } else {
            printf("%d %d\n", 2 * i, 2 * i + 1);
        }
        ++cnt;
    }
}