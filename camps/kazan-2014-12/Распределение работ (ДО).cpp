#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <iomanip>
#include <sstream>
#include <climits>
#include <bitset>
#include <assert.h>
 
#define fi first
#define se second
#define mp make_pair
 
#define sz(a) (int)a.size()
#define len(s) (int)s.length()
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const int INF = 1234567890;
const ll INF_LL = LLONG_MAX - INF;
const int MAXN = 1e6;
const int MAXM = 1e4;
const int MOD = 1e9 + 7;
const double eps = 1e-6;

struct TNode {
 	int L, R;
	int left, right;
	ll key;
};

int tc = 0;
TNode tree[4 * MAXN + 15];

int newNode(int L, int R) {
 	tree[tc].L = L;
	tree[tc].R = R;
	tree[tc].left = tree[tc].right = -1;
	tree[tc].key = 0;

	return tc++;
}

int buildTree(int L, int R) {
 	int root = newNode(L, R);

	if (R - L == 1) {
		return root;
	}

	int M = (L + R) / 2;
	tree[root].left = buildTree(L, M);
	tree[root].right = buildTree(M, R);

	return root;
}

void add(int node, int pos, ll val) {
 	if (tree[node].R - tree[node].L == 1) {
     	tree[node].key += val;
		return;
	}

	int left = tree[node].left;
	int right = tree[node].right;

	if (pos < tree[left].R) {
     	add(left, pos, val);
	} else {
     	add(right, pos, val);
	}

	tree[node].key = tree[left].key + tree[right].key;
}

ll getSum(int node, int L, int R) {
 	if (tree[node].R <= L || R <= tree[node].L) {
     	return 0LL;
	}

	if (L <= tree[node].L && tree[node].R <= R) {
     	return tree[node].key;
	}

	return getSum(tree[node].left, L, R) + getSum(tree[node].right, L, R);
}

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("optimize.in", "r", stdin);
        freopen("optimize.out", "w", stdout);
    #endif

	int n, m;
	cin >> n >> m;

	vector<ll> t(m);
	for (int i = 0; i < m; i++) {
     	cin >> t[i];
	}

	vector<vector<ll> > a(n);
	vector<ll> sum(n);
	for (int i = 0; i < n; i++) {
     	int k;
		cin >> k;
		
		a[i].resize(k);
		for (int j = 0; j < k; j++) {
			cin >> a[i][j];
			--a[i][j];
			sum[i] += t[a[i][j]];
		}
	}

	vector<ll> s(m);
	for (int i = 0; i < n; i++) {
     	for (int j = 0; j < sz(a[i]); j++) {
         	ll col = a[i][j];
			s[col] = sum[i];
		}
	}

	vector<pair<ll, ll> > ds(m);
	for (int i = 0; i < m; i++) {
     	ds[i].fi = s[i] - t[i];
		ds[i].se = i;
	}
	sort(ds.begin(), ds.end());
	vector<pair<ll, ll> > dst(m);
	ll k = 0;
	for (int i = 0; i < m; i++) {
     	if (i > 0 && ds[i].fi == ds[i - 1].fi) {
			--k;
		}
		dst[i].fi = ds[i].se;		
		dst[i].se = k;
		++k;
	}
	sort(dst.begin(), dst.end());

	vector<pair<ll, ll> > st(m);
	for (int i = 0; i < m; i++) {
     	st[i] = mp(t[i], dst[i].se);
	}

	sort(st.begin(), st.end());

	buildTree(0, k);
	vector<int> toadd(1, st[0].se);
	ll ans = 0;
	for (int i = 1; i < m; i++) {
		if (st[i].fi != st[i - 1].fi) {
         	for (int j = 0; j < sz(toadd); j++) {
             	add(0, toadd[j], 1);
			}
			toadd.clear();
		}
     	ans += getSum(0, 0, st[i].se);
		toadd.push_back(st[i].se);
	}

	cout << ans << endl;
}
