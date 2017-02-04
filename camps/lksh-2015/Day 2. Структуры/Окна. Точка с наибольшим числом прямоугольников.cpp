#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair< int, pair<int, int> > PIII;

struct Node {
    Node *l, *r;
    int L, R;
    int key_max, maxid, block;

    Node() : l(nullptr), r(nullptr), L(0), R(0), key_max(0), maxid(0), block(0) {}
    Node(int L, int R) : Node() {
        this->L = L;
        this->R = R;
        maxid = L;
    }

    Node(Node *l, Node *r) : l(l), r(r), block(0) {
        L = l->L;
        R = r->R;
        if (l->key_max > r->key_max) {
            key_max = l->key_max;
            maxid = l->maxid;
        } else {
            key_max = r->key_max;
            maxid = r->maxid;
        }
    }
};

Node *buildTree(int L, int R) {
    if (R - L == 1) return new Node(L, R);
    int M = (L + R) >> 1;
    return new Node(buildTree(L, M), buildTree(M, R));
}

void addVal(Node *node, int val) {
    if (!node) return;
    node->key_max += val;
    node->block += val;
}

void push(Node *node) {
    if (node->block != 0) {
        addVal(node->l, node->block);
        addVal(node->r, node->block);
        node->block = 0;
    }
}

void update(Node *node, int L, int R, int val) {
    if (node->R <= L || R <= node->L) {
        return;
    }
    
    if (L <= node->L && node->R <= R) {
        addVal(node, val);
        return;
    }

    push(node);
    
    update(node->l, L, R, val);
    update(node->r, L, R, val);

    if (node->l->key_max > node->r->key_max) {
        node->key_max = node->l->key_max;
        node->maxid = node->l->maxid;
    } else {
        node->key_max = node->r->key_max;
        node->maxid = node->r->maxid;
    }
}

pair<int, int> getMax(Node *node, int L, int R) {
    if (node->R <= L || R <= node->L) {
        return {-1, -1};
    }

    if (L <= node->L && node->R <= R) {
        return {node->key_max, node->maxid};
    }

    auto left = getMax(node->l, L, R);
    auto right = getMax(node->r, L, R);
    if (left.fi > right.fi) {
        return left;
    } else {
        return right;
    }
}

struct Rect {
    int x1, y1, x2, y2;
};

bool cmp_open(Rect r1, Rect r2) {
    return r1.x1 < r2.x1;
}

bool cmp_close(Rect r1, Rect r2) {
    return r1.x2 < r2.x2;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("windows.in", "r", stdin);
    freopen("windows.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> all;
    vector<Rect> rects_start(n), rects_end;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        rects_start[i] = {x1, y1, x2, y2};
        all.push_back(x1);
        all.push_back(y1);
        all.push_back(x2);
        all.push_back(y2);
    }

    sort(all.begin(), all.end());

    map<int, int> from, to;
    int diff = 0;
    for (int i = 0; i < (int)all.size(); i++) {
        if (to.find(all[i]) == to.end()) {
            to[all[i]] = diff;
            from[diff++] = all[i];
        }
    }

    for (int i = 0; i < n; i++) {
        rects_start[i].x1 = to[rects_start[i].x1];
        rects_start[i].x2 = to[rects_start[i].x2];
        rects_start[i].y1 = to[rects_start[i].y1];
        rects_start[i].y2 = to[rects_start[i].y2];
    }

    rects_end = rects_start;
    sort(rects_start.begin(), rects_start.end(), cmp_open);
    sort(rects_end.begin(), rects_end.end(), cmp_close);

    Node *root = buildTree(0, diff);

    PIII ans = {-1, {-1, -1}};
    for (int i = 0, k1 = 0, k2 = 0; i < diff; i++) {
        while (k1 < n && rects_start[k1].x1 < i) k1++;
        while (k1 < n && rects_start[k1].x1 == i) {
            update(root, rects_start[k1].y1, rects_start[k1].y2 + 1, 1);
            k1++;
        }

        auto current_max = getMax(root, 0, diff);
        PIII cur = {current_max.fi, {i, current_max.se}};
        if (ans < cur) {
            ans = cur;
        }

        while (k2 < n && rects_end[k2].x2 < i) k2++;
        while (k2 < n && rects_end[k2].x2 == i) {
            update(root, rects_end[k2].y1, rects_end[k2].y2 + 1, -1);
            k2++;
        }
    }

    printf("%d\n%d %d\n", ans.fi, from[ans.se.fi], from[ans.se.se]);
}
