#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int INF = 1e9;
const int K = 17;

struct Node {
    Node* to[2] = {nullptr, nullptr};
    int minval = INF;

    void upd_min(int x) {
        minval = min(minval, x);
    }

    void add(int x) {
        Node* node = this;
        for (int i = (1u << K); i >= 0; --i) {
            node->upd_min(x);
            int bit = (x >> i) & 1;
            if (node->to[bit] == nullptr) {
                node->to[bit] = new Node;
            }
            node = node->to[bit];
        }
        node->upd_min(x);
    }
};

int main() {
    int q;
    scanf("%d", &q);

    vector<char> used(N + 1);
    vector<Node*> tries(N + 1, nullptr);
    for (int ii = 0; ii < q; ++ii) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int u;
            scanf("%d", &u);
            if (!used[u]) {
                used[u] = true;
                for (int k = u; k <= N; k += u) {
                    if (tries[k] == nullptr) tries[k] = new Node;
                    tries[k]->add(u);
                }
            }
        } else {
            int x, k, s;
            scanf("%d%d%d", &x, &k, &s);
            s -= x;
        }
    }
}
