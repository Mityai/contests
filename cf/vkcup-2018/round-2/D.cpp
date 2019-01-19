#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const double eps = 1e-8;

struct Node {
	Node *l, *r;
	double key;
    int prior;
	int sz;

	Node() :
		l(nullptr), r(nullptr), key(0), prior(rand()), sz(1) {};

	Node(double key) : Node() {
		this->key = key;
	}
};

int getSize(Node *node) {
	return node ? node->sz : 0;
}

void relax(Node *node) {
	if (!node) return;
	node->sz = 1 + getSize(node->l) + getSize(node->r);
}

Node *merge(Node *left, Node *right) {
	if (!left) return right;
	if (!right) return left;

	if (left->prior > right->prior) {
		left->r = merge(left->r, right);
		relax(left);
		return left;
	} else {
		right->l = merge(left, right->l);
		relax(right);
		return right;
	}
}

void split(Node *node, double key, Node *&left, Node *&right) {
	if (!node) {
		left = right = nullptr;
		return;
	}

	if (node->key <= key) {
		split(node->r, key, node->r, right);
		left = node;
		relax(left);
	} else {
		split(node->l, key, left, node->l);
		right = node;
		relax(right);
	}
}

void insert(Node *&root, double x) {
	Node *A, *B;
	split(root, x, A, B);
	root = merge(A, new Node(x));
	root = merge(root, B);
}

int greatr(Node *&root, double x) {
    Node *A, *B;
    split(root, x - eps, A, B);
    int res = getSize(B);
    root = merge(A, B);
    return res;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    double w;
    while (scanf("%d%lf", &n, &w) == 2) {
        map<double, vector<double>> mp;
        for (int i = 0; i < n; ++i) {
            double x, v;
            scanf("%lf%lf", &x, &v);

            double t1 = fabs(x / (v - w));
            double t2 = fabs(x / (v + w));
            if (t1 > t2) {
                swap(t1, t2);
            }
            mp[t1].push_back(t2);
        }

        Node *root = nullptr;

        ll ans = 0;
        for (auto& v : mp) {
            ans += (v.second.size() * (v.second.size() - 1)) / 2;
            sort(v.second.begin(), v.second.end());
            for (double key : v.second) {
                ans += greatr(root, key);
                insert(root, key);
            }
        }

        printf("%lld\n", ans);
    }
}
