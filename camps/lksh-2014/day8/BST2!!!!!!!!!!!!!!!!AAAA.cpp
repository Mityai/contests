#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <climits>

typedef long long ll;

using namespace std;

const int MAXN = 1000000;

struct TNode {
    int x, y;
    int left, right;
    int w;
};

int root = -1;
TNode tree[MAXN];

int getW(int node) {
    if (node == -1) {
        return 0;
    }

    return tree[node].w;
}

void relax(int node) {
    if (node == -1) {
        return;
    }

    int left = tree[node].left;
    int right = tree[node].right;

    tree[node].w = 1 + getW(left) + getW(right);
}

void split(int node, int c, int &left, int &right) {
    if (node == -1) {
        left = right = -1;
        return;
    }

    if (tree[node].x <= c) {
        split(tree[node].right, c, left, right);
        tree[node].right = left;
        left = node;
        relax(left);
    } else {
        split(tree[node].left, c, left, right);
        tree[node].left = right;
        right = node;
        relax(right);
    }
}

int _merge(int left, int right) {
    if (left == -1) {
        return right;
    }

    if (right == -1) {
        return left;
    }

    if (tree[left].y < tree[right].y) {
        tree[left].right = _merge(tree[left].right, right);
        relax(left);
        return left;
    } else {
        tree[right].left = _merge(left, tree[right].left);
        relax(right);
        return right;
    }
}

void _insert(int node) {
    int left = -1, right = -1;
    split(root, tree[node].x, left, right);

    left = _merge(left, node);

    root = _merge(left, right);
}

void remove(int x) {
    int left = -1, right = -1;
    int A = -1, B = -1;
    split(root, x, left, right);

    B = right;

    split(left, x - 1, A, right);

    root = _merge(A, B);
}

bool _find(int node, int x) {
    if (node == -1) {
        return false;
    }

    if (tree[node].x < x) {
        if (tree[node].right == -1) {
            return false;
        }

        return _find(tree[node].right, x);
    } else if (tree[node].x > x) {
        if (tree[node].left == -1) {
            return false;
        }

        return _find(tree[node].left, x);
    }

    return true;
}

int getMaxLeft(int node) {
    int left = tree[node].left;

    if (left == -1) {
        return tree[node].x;
    }

    return getMaxLeft(left);
}

int getMinRight(int node) {
    int right = tree[node].right;

    if (right == -1) {
        return tree[node].x;
    }

    return getMinRight(right);
}

int next(int x) {
    int left = -1, right = -1;
    split(root, x, left, right);

    if (right == -1) {
        return x;
    }

    int res = getMaxLeft(right);

    root = _merge(left, right);

    return res;
}

int prev(int x) {
    int left = -1, right = -1;
    split(root, x - 1, left, right);

    if (left == -1) {
        return x;
    }

    int res = getMinRight(left);

    root = _merge(left, right);

    return res;
}

int kth(int node, int k) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (left == -1 && right == -1) {
        return tree[node].x;
    }

    if (left == -1) {
        kth(right, k);
    }


    if (k <= tree[left].w) {
        return kth(left, k);
    }

    if (k == tree[left].w + 1) {
        return tree[node].x;
    }

    return kth(right, k - (tree[left].w + 1));
}

int tc = 0;

int newNode(int x) {
    tree[tc].x = x;
    tree[tc].y = rand();
    tree[tc].left = -1;
    tree[tc].right = -1;

    return tc++;
}

int main() {
    freopen("bst2.in", "r", stdin);
    freopen("bst2.out", "w", stdout);

    string s;
    while (cin >> s) {
        int n;
        cin >> n;

        if (s == "insert") {
            if (!_find(root, n)) {
                int node = newNode(n);
                _insert(node);
            }
        }

        if (s == "delete") {
            if (_find(root, n)) {
                remove(n);
            }
        }

        if (s == "exists") {
            if (_find(root, n)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        }

        if (s == "next") {
            if (root == -1) {
                cout << "none" << endl;
                continue;
            }

            int next_n = next(n);
            
            if (next_n == n) {
                cout << "none" << endl;
            } else {
                cout << next_n << endl;
            }
        }

        if (s == "prev") {
            if (root == -1) {
                cout << "none" << endl;
                continue;
            }

            int prev_n = prev(n);
            
            if (prev_n == n) {
                cout << "none" << endl;
            } else {
                cout << prev_n << endl;
            }
        }

        if (s == "kth") {
            if (root == -1) {
                cout << "none" << endl;
                continue;
            }

            if (tree[root].w < n) {
                cout << "none" << endl;
            } else {
                cout << kth(root, n) << endl;
            }
        }
    }
}
