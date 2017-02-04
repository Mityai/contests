#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

struct Node {
    Node *l, *r;
    int L, R;
    ll val, keyGcd;

    Node() : l(nullptr), r(nullptr), val(0), keyGcd(0) {};

    Node(Node *l, Node *r) : l(l), r(r) {
        keyGcd = gcd(abs(l->keyGcd), abs(r->keyGcd));
        L = l->L;
        R = r->R;
    }

    Node(int L, int R) : Node() {
        this->L = L;
        this->R = R;
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) {
        return new Node(L, R);
    }
    int M = (L + R) >> 1;
    return new Node(buildTree(L, M), buildTree(M, R));
}

ll getGCD(Node *node, int L, int R) {
    if (R <= node->L || node->R <= L) {
        return 0;
    }

    if (L <= node->L && node->R <= R) {
        return node->keyGcd;
    }

    return gcd(getGCD(node->l, L, R), getGCD(node->r, L, R));
}

void add(Node *node, int pos, ll val) {
    if (node->R - node->L == 1) {
        node->val += val;
        node->keyGcd = abs(node->val);
        return;
    }

    if (pos < node->l->R) {
        add(node->l, pos, val);
    } else {
        add(node->r, pos, val);
    }

    node->keyGcd = gcd(node->l->keyGcd, node->r->keyGcd);
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#endif

    Node *root = buildTree(0, (1 << 20));

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        int t;
        scanf("%d", &t);

        if (t == 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", getGCD(root, l - 1, r));
        } else {
            int pos;
            ll val;
            scanf("%d%lld", &pos, &val);
            add(root, pos - 1, val);
        }
    }
}
