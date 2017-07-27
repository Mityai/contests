#include <bits/stdc++.h>
#define left sdjflkasfasdf
#define right sadaskdjkljw
#define fi first
#define se second
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

typedef long long ll;

const int INF = 1e9;

struct Node {
    int L, R;
    Node* l;
    Node* r;
    int mn, mx;
    int mnid, mxid;

    Node() {
    }

    Node(int L, int R, int val) :
        L(L), R(R), l(nullptr), r(nullptr), mn(val), mx(val), mnid(L), mxid(L) {
    }

    Node(Node* l, Node* r) :
        L(l->L), R(r->R), l(l), r(r), mn(min(l->mn, r->mn)), mx(max(l->mx, r->mx)) {
        if (l->mn == mn) mnid = l->mnid;
        else mnid = r->mnid;
        if (l->mx == mx) mxid = l->mxid;
        else mxid = r->mxid;
    }
};

Node* buildTree(int L, int R, const vector<int>& a) {
    if (R - L == 1) return new Node(L, R, a[L]);
    int M = (L + R) / 2;
    return new Node(buildTree(L, M, a), buildTree(M, R, a));
}

void setinf(Node* node, int pos) {
    if (node->R - node->L == 1) {
        node->mn = INF;
        node->mx = -INF;
        return;
    }
    if (pos < node->l->R) setinf(node->l, pos);
    else setinf(node->r, pos);
    if (node->l->mn < node->r->mn) {
        node->mn = node->l->mn, node->mnid = node->l->mnid;
    } else {
        node->mn = node->r->mn, node->mnid = node->r->mnid;
    }
    if (node->l->mx > node->r->mx) {
        node->mx = node->l->mx, node->mxid = node->l->mxid;
    } else {
        node->mx = node->r->mx, node->mxid = node->r->mxid;
    }
}

pair<int, int> getmin(Node* node, int L, int R) {
    if (node->R <= L || R <= node->L) return {INF, 0};
    if (L <= node->L && node->R <= R) return {node->mn, node->mnid};
    auto left = getmin(node->l, L, R);
    auto right = getmin(node->r, L, R);
    return min(left, right);
}

pair<int, int> getmax(Node* node, int L, int R) {
    if (node->R <= L || R <= node->L) return {-INF, 0};
    if (L <= node->L && node->R <= R) return {node->mx, node->mxid};
    auto left = getmax(node->l, L, R);
    auto right = getmax(node->r, L, R);
    return max(left, right);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    Node* root = buildTree(0, n, a);

    vector<vector<int>> to_min(n);
    vector<vector<int>> to_max(n);
    vector<int> mx_here(n), mn_here(n);
    pair<int, int> mn = {a[0], 0};
    pair<int, int> mx = {a[0], 0};

    set<pair<int, int>> good;
    for (int i = 0; i < n; ++i) {
        if (a[i] < mn.fi) {
            mn = {a[i], i};
        }
        if (a[i] > mx.fi) {
            mx = {a[i], i};
        }
        to_min[mn.se].push_back(i);
        to_max[mx.se].push_back(i);
        mn_here[i] = mn.fi;
        mx_here[i] = mx.fi;
        if (a[i] - mn_here[i] <= k && mx_here[i] - a[i] <= k) {
            good.insert({a[i], i});
        }
    }

    vector<char> used(n);
    for (int i = 0; i < n; ++i){
        auto v = *good.begin();
        good.erase(good.begin());
        printf("%d ", v.fi);

        used[v.se] = true;
        setinf(root, v.se);

        for (int ptr : to_min[v.se]) {
            if (used[ptr]) continue;
            if (good.find({a[ptr], ptr}) == good.end()) {
                auto mn = getmin(root, 0, ptr + 1);
                to_min[mn.se].push_back(ptr);
                mn_here[ptr] = mn.fi;
                if (a[ptr] - mn_here[ptr] <= k && mx_here[ptr] - a[ptr] <= k) {
                    good.insert({a[ptr], ptr});
                }
            }
        }
        for (int ptr : to_max[v.se]) {
            if (used[ptr]) continue;
            if (good.find({a[ptr], ptr}) == good.end()) {
                auto mx = getmax(root, 0, ptr + 1);
                to_max[mx.se].push_back(ptr);
                mx_here[ptr] = mx.fi;
                if (a[ptr] - mn_here[ptr] <= k && mx_here[ptr] - a[ptr] <= k) {
                    good.insert({a[ptr], ptr});
                }
            }
        }
    }
    puts("");
}
