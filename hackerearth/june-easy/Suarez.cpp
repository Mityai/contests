#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

struct Node {
    Node* l;
    Node* r;
    int y;
    int sz;
    pair<int, int> x;

    Node() {}
    Node(pair<int, int> xs) : l(nullptr), r(nullptr), y(rand()), sz(1), x(xs) {
    }
};

int getsize(Node* node) {
    return node ? node->sz : 0;
}

void relax(Node* node) {
    if (!node) return;
    node->sz = 1 + getsize(node->l) + getsize(node->r);
}

void splitk(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (getsize(node->l) >= k) {
        splitk(node->l, k, left, node->l);
        right = node;
        relax(right);
    } else {
        splitk(node->r, k - getsize(node->l) - 1, node->r, right);
        left = node;
        relax(left);
    }
}

void split(Node* node, pair<int, int> x, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (node->x <= x) {
        split(node->r, x, node->r, right);
        left = node;
        relax(left);
    } else {
        split(node->l, x, left, node->l);
        right = node;
        relax(right);
    }
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    if (left->y > right->y) {
        left->r = merge(left->r, right);
        relax(left);
        return left;
    } else {
        right->l = merge(left, right->l);
        relax(right);
        return right;
    }
}

Node* root = nullptr;

void insert(pair<int, int> x) {
    Node* A;
    Node* B;
    split(root, x, A, B);
    root = merge(A, new Node(x));
    root = merge(root, B);
}

void erase(pair<int, int> x) {
    Node* A;
    Node* B;
    split(root, x, A, B);
    Node* C;
    splitk(A, getsize(A) - 1, A, C);
    root = merge(A, B);
}

int getkth(int k) {
    Node* A;
    Node* B;
    Node* C;
    splitk(root, k - 1, A, B);
    splitk(B, 1, B, C);
    int ret;
    if (getsize(B) == 0) {
        ret = -1;
    } else {
        ret = B->x.fi;
    }
    root = merge(A, B);
    root = merge(root, C);
    return ret;
}

vector<int> ls, rs;

bool cmpo(pair<int, int> a, pair<int, int> b) {
    return ls[a.se] < ls[b.se];
}

bool cmpc(pair<int, int> a, pair<int, int> b) {
    return rs[a.se] < rs[b.se];
}

int main() {
    srand(time(NULL));

    int n;
    scanf("%d", &n);

    set<int> all;
    vector<pair<int, int>> op(n), cl(n);
    ls.resize(n); rs.resize(n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        ls[i] = l;
        rs[i] = r;
        op[i] = {r - l + 1, i};
        cl[i] = {r - l + 1, i};
        all.insert(l);
        all.insert(r);
    }

    sort(op.begin(), op.end(), cmpo);
    sort(cl.begin(), cl.end(), cmpc);

    int q;
    scanf("%d", &q);

    vector<pair<int, int>> pts(q);
    vector<int> needk(q);
    for (int i = 0; i < q; ++i) {
        int x;
        scanf("%d%d", &needk[i], &x);
        pts[i] = {x, i};
        all.insert(x);
    }
    vector<int> ans(q);
    sort(pts.begin(), pts.end());

    int i = 0, j = 0, p = 0;
    for (int x : all) {
        while (i < n && ls[op[i].se] <= x) {
            insert(op[i]);
            ++i;
        }

        while (p < q && pts[p].fi <= x) {
            int k = needk[pts[p].se];
            ans[pts[p].se] = getkth(k);
            ++p;
        }

        while (j < n && rs[cl[j].se] <= x) {
            erase(cl[j]);
            ++j;
        }
    }

    for (int x : ans) {
        printf("%d\n", x);
    }
}
