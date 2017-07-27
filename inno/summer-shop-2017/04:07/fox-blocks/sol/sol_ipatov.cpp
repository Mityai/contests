#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const int MAXN = 400000;

ll dd[MAXN * 4];
vector<int> aa[MAXN];
ll h[MAXN];
vector<int> vv;
int n, q;

void add(int v, int tl, int tr, int l, int r, ll d) {
	if (r <= tl || tr <= l)
		return;
	if (l <= tl && tr <= r) {
		dd[v] += d;
		if (dd[v] >= MOD)
			dd[v] -= MOD;
		return;
	}
	int m = (tl + tr) >> 1;
	add(v * 2 + 1, tl, m, l, r, d);
	add(v * 2 + 2, m, tr, l, r, d);
}

ll get(int v, int tl, int tr, int x) {
	if (tl + 1 == tr)
		return dd[v];
	int m = (tl + tr) >> 1;
	if (x < m)
		return (get(v * 2 + 1, tl, m, x) + dd[v]) % MOD;
	else
		return (get(v * 2 + 2, m, tr, x) + dd[v]) % MOD;
}



int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++i)
		scanf("%d", &h[i]);
	for (int i = 0; i < q; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a;
		--b;
		aa[b].push_back(a);
	}

	ll ans = 0;


	for (int i = 0; i < n; ++i) {
		int lst = 0;
		while (!vv.empty() && h[vv[vv.size() - 1]] <= h[i]) {
			add(0, 0, n, 0, vv[vv.size() - 1] + 1, ((ll)(i - vv[vv.size() - 1] - 1) * (h[vv[vv.size() - 1]] - lst)) % MOD );
			lst = h[vv[vv.size() - 1]];
			vv.pop_back();
		}
		if (!vv.empty()) {
			int x = vv[vv.size() - 1];
			add(0, 0, n, 0, x + 1, ((ll)(h[i] - lst) * (i - x - 1)) % MOD);
		}
		vv.push_back(i);
		for (int j = 0; j < (int)aa[i].size(); ++j) {
			ans += get(0, 0, n, aa[i][j]);
			if (ans >= MOD)
				ans -= MOD;
		}
	}

	cout << ans;

	return 0;
}
