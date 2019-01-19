#include <bits/stdc++.h>
using namespace std;

using ui = unsigned int;

struct Node {
    Node* child[2] = {nullptr, nullptr};
    int ended = 0;
};

void add(Node* root, ui elem) {
    Node* node = root;
    for (int i = 29; i >= 0; --i) {
        int bit = (elem >> i) & 1;
        if (node->child[bit] == nullptr) {
            node->child[bit] = new Node;
        }
        node = node->child[bit];
        ++node->ended;
    }
}

ui get_min_elem(Node* root, ui elem) {
    Node *node = root;
    ui ans = 0;
    for (int i = 29; i >= 0; --i) {
        int bit = (elem >> i) & 1;
        if (node->child[bit] == nullptr || node->child[bit]->ended == 0) {
            bit ^= 1;
        }
        ans |= ((1u << i) & elem) ^ (bit << i);
        node = node->child[bit];
        --node->ended;
    }
    return ans;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        vector<ui> a(n);
        for (int i = 0; i < n; ++i) {
            scanf("%u", &a[i]);
        }

        Node* root = new Node;
        for (int i = 0; i < n; ++i) {
            ui P;
            scanf("%u", &P);
            add(root, P);
        }

        for (int i = 0; i < n; ++i) {
            printf("%u ", get_min_elem(root, a[i]));
        }
        putchar('\n');
    }
}
