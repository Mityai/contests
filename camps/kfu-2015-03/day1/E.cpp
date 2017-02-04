#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;

const int N = 1 << 17;

ui f[N];

ui a, b;
ui cur = 0;

inline ui nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

inline ui nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

struct Node {
    int L, R;
    Node *l, *r;
    vector<ui> sr;

    Node() {}
    Node(int L, int R) : L(L), R(R), l(nullptr), r(nullptr) {
        sr.push_back(f[L]);
    }
    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        int i = 0, j = 0;
        while (i < l->sr.size() || j < r->sr.size()) {
            if (i == l->sr.size()) {
                while (j < r->sr.size()) {
                    sr.push_back(r->sr[j]);
                    j++;
                }
            } else if (j == r->sr.size()) {
                while (i < l->sr.size()) {
                    sr.push_back(l->sr[i]);
                    i++;
                }
            } else {
                if (l->sr[i] < r->sr[j]) {
                    sr.push_back(l->sr[i]);
                    i++;
                } else {
                    sr.push_back(r->sr[j]);
                    j++;
                }
            }
        }
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) >> 1;
    return new Node(buildTree(L, M), buildTree(M, R));
}

int getcnt(Node *node, int L, int R, ui val) {
    if (node->R <= L || R <= node->L) return 0;
    if (L <= node->L && node->R <= R) {
        return upper_bound(node->sr.begin(), node->sr.end(), val) - node->sr.begin();
    }
    return getcnt(node->l, L, R, val) + getcnt(node->r, L, R, val);
}

int main() {
    freopen("find2d.in", "r", stdin);
    freopen("find2d.out", "w", stdout);

    int q;
    scanf("%d", &q);

    scanf("%u%u", &a, &b);

    for (int i = 0; i < N; i++) {
        f[i] = nextRand24();
    }

    Node *root = buildTree(0, N);

    ui ans = 0;
    for (int i = 0; i < q; i++) {
        ui l = nextRand17();
        ui r = nextRand17();
        if (l > r) swap(l, r);
        ui x = nextRand24();
        ui y = nextRand24();
        if (x > y) swap(x, y);
        //ui c = cnt(r + 1, y) - cnt(r + 1, x - 1) - cnt(l, y) + cnt(l, x - 1);
        ui c = getcnt(root, 0, r + 1, y) - getcnt(root, 0, r + 1, x - 1) - getcnt(root, 0, l, y) + getcnt(root, 0, l, x - 1);
        //cout << l << ' ' << r << ' ' << x << ' ' << y << ' ' << c << endl;
        b += c;
        ans += c;
    }

    printf("%u\n", ans);
}
