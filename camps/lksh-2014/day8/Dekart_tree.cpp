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
};

int root = -1;
TNode tree[MAXN];

void split(int node, int c, int &left, int &right) {
    if (node == -1) {
        left = right = -1;
        return;
    }

    if (tree[node].x <= c) {
        split(tree[node].right, c, left, right);
        tree[node].right = left;
        left = node;
    } else {
        split(tree[node].left, c, left, right);
        tree[node].left = right;
        right = node;
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
        return left;
    } else {
        tree[right].left = _merge(left, tree[right].left);
        return right;
    }
}

int tc = 0;

int newNode(int x) {
    tree[tc].x = x;
    tree[tc].y = rand();
    tree[tc].left = -1;
    tree[tc].right = -1;

    return tc++;
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

bool exists(int node, int x) {
    if (node == -1) {
        return false;
    }

    if (tree[node].x < x) {
        if (tree[node].right == -1) {
            return false;
        }

        return exists(tree[node].right, x);
    } else if (tree[node].x > x) {
        if (tree[node].left == -1) {
            return false;
        }

        return exists(tree[node].left, x);
    }

    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string s;
    while (cin >> s) {
        int n;
        cin >> n;

        if (s[0] == 'i') {
            if (!exists(root, n)) {
                int node = newNode(n);
                _insert(node);
            }
        }

        if (s[0] == 'd') {
            if (exists(root, n)) {
                remove(n);
            }
        }

        if (s[0] == 'e') {
            if (exists(root, n)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        }
    }
}
