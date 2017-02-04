#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = int(1e5);

struct Node {
    Node *l, *r;
    int L, R;
    int sum;

    Node() {}

    Node(int L, int R) : L(L), R(R), sum(0) {}

    Node(int L, int R, int val) : Node(L, R) {
        sum = val;
    };

    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        sum = l->sum + r->sum;
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) >> 1;
    return new Node(buildTree(L, M), buildTree(M, R));
}

int getSum(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) {
        return 0;
    }

    if (L <= node->L && node->R <= R) {
        return node->sum;
    }

    return getSum(node->l, L, R) + getSum(node->r, L, R);
}

Node *setVal(Node *node, int pos, int val) {
    if (node->R - node->L == 1) {
        return new Node(node->L, node->R, val);
    }

    Node *left = node->l;
    Node *right = node->r;
    if (pos < node->l->R) {
        left = setVal(node->l, pos, val);
    } else {
        right = setVal(node->r, pos, val);
    }
    return new Node(left, right);
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("rollback.in", "r", stdin);
    freopen("rollback.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    Node *root[n + 1];
    root[0] = buildTree(0, n + 1);

    int pos[m + 1];
    memset(pos, -1, sizeof pos);

    for (int i = 1; i <= n; i++) {
        if (pos[a[i]] != -1) {
            root[i] = setVal(root[i - 1], pos[a[i]], 0);
            root[i] = setVal(root[i], pos[a[i]] = i, 1);
        } else {
            root[i] = setVal(root[i - 1], pos[a[i]] = i, 1);
        }
    }

    int q;
    scanf("%d", &q);

    int p = 0;
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        int from = (x + p) % n + 1;
        int k = (y + p) % m + 1;

        int l = from - 1, r = n + 1;

        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            int cnt = getSum(root[mid], from, mid + 1);
            if (cnt < k) {
                l = mid;
            } else {
                r = mid;
            }
        }

        if (r == n + 1) {
            r = 0;
        }
        p = r;
        printf("%d\n", p);
    }
}
