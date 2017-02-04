#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1234567890;

struct Node {
	Node *left, *right;
	int key, x, y, w;

	Node() : left(NULL), right(NULL) {};
	Node(int key) : left(NULL), right(NULL), key(key) {
		x = key;
		y = rand();
		w = 1;
	}
};

Node *root = NULL;

int getW(Node *node) {
	if (!node) return 0;
	return node->w;
}

int getVal(Node *node) {
	if (!node) return INF;
	return node->key;
}

void relax(Node *node) {
	if (!node) return;
	node->w = 1 + getW(node->left) + getW(node->right);
	node->key = min(node->x, min(getVal(node->left), getVal(node->right)));
}

void split(Node *node, int k, Node *&left, Node *&right) {
	if (!node) {
		left = right = NULL;
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

void _insert(int x, int pos) {
	Node *A, *B;
	split(root, pos, A, B);
	root = _merge(A, new Node(x));
	root = _merge(root, B);
}

void find_min(Node *node, int &k) {
	if (node->x == node->key) {
		k += getW(node->left);
		return;
	}

	if (node->left->key == node->key) {
		find_min(node->left, k);
	} else {
		k += getW(node->left) + 1;
		find_min(node->right, k);
	}
}

vector<int> ans;

int make_me_happy(int r) {
	Node *A, *B, *C;
	split(root, r, A, C);

	int k = 0;
	find_min(A, k);

	split(A, k, A, B);
	Node *trash;
	split(B, 1, trash, B);
	root = _merge(A, B);
	root = _merge(root, C);

	ans.push_back(trash->x);

	return k;
}

void go(Node *node) {
	if (!node) return;
	go(node->left);
	ans.push_back(node->x);
	go(node->right);
}

void print(Node *node) {
	if (!node) return;
	print(node->left);
	cout << node->x << ' ';
	print(node->right);
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout); 
#else
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#endif

    int n;
    ll k;
    scanf("%d%lld", &n, &k);

    for (int i = 0; i < n; i++) {
    	int x;
    	scanf("%d", &x);

    	_insert(x, i);
    }

    int cnt = 0;
    while (k > 0 && cnt++ < n) {
    	k -= make_me_happy(k + 1);
    }
    go(root);

    for (int i = 0; i < n; i++) {
    	cout << ans[i] << ' ';
    }
    cout << endl;
}
