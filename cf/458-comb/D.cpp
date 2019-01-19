#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5e5;

int gcd(int a, int b) {
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int a[N];

struct Node {
    Node* l;
    Node* r;
    int L, R;
    int g;

    Node()
        : l(nullptr), r(nullptr)
    {
    }

    Node(int L, int R)
        : l(nullptr), r(nullptr)
        , L(L), R(R), g(a[L])
    {
    }

    Node(Node* l, Node* r)
        : l(l), r(r), L(l->L), R(r->R), g(gcd(l->g, r->g))
    {
    }
};

Node* buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void update(Node* node, int pos, int val) {
    if (node->R - node->L == 1) {
        node->g = val;
        return;
    }
    if (pos < node->l->R) update(node->l, pos, val);
    else update(node->r, pos, val);
    node->g = gcd(node->l->g, node->r->g);
}

int gcd(Node* node, int L, int R) {
    if (node->R <= L || R <= node->L) return 0;
    if (L <= node->L && node->R <= R) return node->g;
    return gcd(gcd(node->l, L, R), gcd(node->r, L, R));
}

inline int readInt() {
    int c = getchar();
    while (c <= 32) c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') {
        ret = ret * 10 + c - '0';
        c = getchar();
    }
    return ret;
}

int main() {
    int n = readInt();

    for (int i = 0; i < n; ++i) {
        a[i] = readInt();
    }

    Node* root = buildTree(0, n);

    int q = readInt();

    for (int i = 0; i < q; ++i) {
        int t = readInt();

        if (t == 1) {
            int l = readInt();
            int r = readInt();
            int x = readInt();
            --l, --r;

            if (l == r) {
                puts("YES");
                continue;
            } else if (l + 1 == r) {
                if (a[l] % x == 0 || a[r] % x == 0) {
                    puts("YES");
                } else {
                    puts("NO");
                }
                continue;
            }

            int ri;
            {
                int lb = l - 1, rb = r + 1;
                while (lb + 1 < rb) {
                    int mb = (lb + rb) / 2;
                    if (gcd(root, lb + 1, mb + 1) % x == 0) {
                        lb = mb;
                    } else {
                        rb = mb;
                    }
                }
                ri = lb;
            }
            if (ri + 1 >= r || gcd(root, ri + 2, r + 1) % x == 0) {
                puts("YES");
            } else {
                puts("NO");
            }
        } else {
            int p = readInt();
            int x = readInt();
            a[p - 1] = x;
            update(root, p - 1, x);
        }
    }
}
