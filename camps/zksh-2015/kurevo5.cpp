#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

typedef long long ll;

struct Node {
	Node *left, *right;
	int w, x, sum, y;

	Node() : left(nullptr), right(nullptr) {}
	Node(int x) : left(nullptr), right(nullptr), x(x) {
		sum = x;
		y = rand();
		w = 1;
	}
};

int getW(Node *node) {
	if (!node) return 0;
	return node->w;
}

int getSum(Node *node) {
	if (!node) return 0;
	return node->sum;
}

void relax(Node *node) {
	if (!node) return;
	node->w = 1 + getW(node->left) + getW(node->right);
	node->sum = node->x + getSum(node->left) + getSum(node->right);
}

void split(Node *node, int k, Node *&left, Node *&right) {
	if (!node) {
		left = right = nullptr;
		return;
	}

	if (getW(node->left) < k) {
		split(node->right, k - getW(node->left) - 1, node->right, right);
		left = node;
		relax(left);
	} else {
		split(node->left, k, left, node->left);
		right = node;
		relax(right);
	}
}

Node *_merge(Node *left, Node *right) {
	if (!left) return right;
	if (!right) return left;

	if (left->y > right->y) {
		left->right = _merge(left->right, right);
		relax(left);
		return left;
	} else {
		right->left = _merge(left, right->left);
		relax(right);
		return right;
	}
}

int n;
Node *roots[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};

void _insert(Node *&root, int x) {
	root = _merge(root, new Node(x));
}

void print(Node *node) {
	if (!node) return;

	print(node->left);
	cout << node->x << ' ';
	print(node->right);
}

int getSumRoot(Node *root, int l, int r) {
	Node *A, *B, *C;
	split(root, r, B, C);
	split(B, l, A, B);
	int ret = getSum(B);
	root = _merge(A, B);
	root = _merge(root, C);
	return ret;
}

int getSum(int l, int r) {
	int ret = 0;
	for (int i = 0; i < 5; i++) {
		ret += getSumRoot(roots[i], (l + 4 - i) / 5, (r + 4 - i) / 5);
	}
	return ret;
}

void swapPerm(vector<int> perm) {
	Node *temp[5];
	for (int i = 0; i < 5; i++) {
		temp[i] = roots[i];
	}

	for (int i = 0; i < 5; i++) {
		roots[i] = temp[perm[i]];
	}
}

void moveTree(int k) {
	for (int i = 0; i < 5; i++) {
		Node *&root = roots[i];
		int moveK = (k + 4 - i) / 5;
		Node *A, *B;
		split(root, moveK, A, B);
		root = _merge(B, A);
	}

	for (int i = 0; i < k % 5; i++) {
		for (int j = 0; j < 4; j++) {
			swap(roots[j], roots[j + 1]);
		}
	}
}

int main() {
#if __APPLE__
     freopen("input.txt", "r", stdin);
     freopen("output.txt", "w", stdout);
#else
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#endif

	scanf("%d", &n);

	for (int i = 0; i < 5 * n; i++) {
		int x;
		scanf("%d", &x);

		_insert(roots[i % 5], x);
	}

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		char c;
		scanf(" %c", &c);

		if (c == '?') {
			int l, r;
			scanf("%d%d", &l, &r);

			printf("%d\n", getSum(l - 1, r));
		} else if (c == '<') {
			int k;
			scanf("%d", &k);

			moveTree(k);
		} else if (c == '#') {
			vector<int> perm(5);
			for (int j = 0; j < 5; j++) {
				scanf("%d", &perm[j]);
				--perm[j];
			}

			swapPerm(perm);
		}
	}
}
