#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = int((1LL << 31LL) - 1LL);

vector<int> a;

struct Node {
    Node *l, *r;
    int L, R;
    int key_min;

    Node() {}

    Node(int L, int R) : L(L), R(R) {
        key_min = a[L];
    }

    Node(Node *l, Node *r) : l(l), r(r) {
        L = l->L;
        R = r->R;
        key_min = min(l->key_min, r->key_min);
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) >> 1;
    return new Node(buildTree(L, M), buildTree(M, R));
}

int getMin(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) {
        return INF;
    }

    if (L <= node->L && node->R <= R) {
        return node->key_min;
    }

    return min(getMin(node->l, L, R), getMin(node->r, L, R));
}

struct Query {
    int a, b, v;
};

bool cmp_a(Query q1, Query q2) {
    return q1.a < q2.a;
}

bool cmp_b(Query q1, Query q2) {
    return q1.b < q2.b;
}

struct cmpMax {
    bool operator() (int a, int b) {
        return a > b;
    }
};

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    a.resize(n, INF);

    vector<Query> qstart(m), qend;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &qstart[i].a, &qstart[i].b, &qstart[i].v);
        --qstart[i].a, --qstart[i].b;
    }
    qend = qstart;

    sort(qstart.begin(), qstart.end(), cmp_a);
    sort(qend.begin(), qend.end(), cmp_b);

    multiset<int, cmpMax> cur_queries;
    for (int i = 0, k1 = 0, k2 = 0; i < n; i++) {
        while (k1 < m && qstart[k1].a < i) k1++;
        while (k1 < m && qstart[k1].a == i) {
            cur_queries.insert(qstart[k1].v);
            k1++;
        }

        if (!cur_queries.empty()) {
            int cur_val = *cur_queries.begin();
            a[i] = cur_val;
        }

        while (k2 < m && qend[k2].b < i) k2++;
        while (k2 < m && qend[k2].b == i) {
            auto to_del = cur_queries.find(qend[k2].v);
            if (to_del != cur_queries.end()) {
                cur_queries.erase(cur_queries.find(qend[k2].v));
            }
            k2++;
        }
    }

    Node *root = buildTree(0, n);

    for (int i = 0; i < m; i++) {
        if (getMin(root, qstart[i].a, qstart[i].b + 1) != qstart[i].v) {
            puts("inconsistent");
            return 0;
        }
    }

    puts("consistent");
    for (int x : a) {
        printf("%d ", x);
    }
    printf("\n");
}
