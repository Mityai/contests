#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

#define PROBLEM "xx"

typedef long long ll;

using namespace std;

vector<int> t;

void update(int v, int l0, int r0, int pos, int val) {
	if (l0 == r0) {
		t[v] = val;
	} else {
		int m = (l0 + r0) / 2;
		if (pos <= m)
			update (v * 2, l0, m, pos, val);
		else
			update (v * 2 + 1, m + 1, r0, pos, val);
		t[v] = max(t[v * 2], t[v * 2 + 1]);
	}
}

int get_max(int v, int l0, int r0, int l, int r) {
	if (l > r) 				return 0;
	if (l == l0 && r == r0) return t[v];
	
	int m = (l0 + r0) / 2;
	return max(get_max(v * 2, l0, m, l, min(r, m)), 
			   get_max(v * 2 + 1, m + 1, r0, max(l, m + 1), r));
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);

    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);

    vector<vector<int> > tm(n, vector<int> (n));
    for (int ii = 0; ii < m; ii++) {
    	int i, j;
    	scanf("%d%d", &i, &j);
    	--i, --j;
    	tm[i][j] = ii + 1;
    }

    // for (int i = 0; i < n; i++) {
    // 	for (int j = 0; j < n; j++) {
    // 		cout << tm[i][j] << ' ';
    // 	}
    // 	cout << endl;
    // }

    int ans = INT_MAX;

    for (int i = 0; i < n; i++) {
    	int cur = 0;
    	t.assign(4 * n, 0);
    	for (int j = 0; j < n; j++) {
    		if (tm[i][j]) {
    			cur++;
    			update(1, 0, n - 1, j, tm[i][j]);
    		} else {
    			cur = 0;
    		}
    		if (cur >= k) {
    			ans = min(ans, get_max(1, 0, n - 1, j - k + 1, j));
    		}
    	}
    }

    for (int i = 0; i < n; i++) {
    	int cur = 0;
    	t.assign(4 * n, 0);
    	for (int j = 0; j < n; j++) {
    		if (tm[j][i]) {
    			cur++;
    			update(1, 0, n - 1, j, tm[j][i]);
    		} else {
    			cur = 0;
    		}
    		if (cur >= k) {
    			ans = min(ans, get_max(1, 0, n - 1, j - k + 1, j));
    		}
    	}
    }

	for (int s = 0; s <= 2 * (n - 1); s++) {
		int cur = 0;
		t.assign(4 * n, 0);
		for (int i = 0; i <= s && i < n; i++) {
			int j = s - i;
			if (i < n && j < n) {
				if (tm[i][j]) {
					cur++;
					update(1, 0, n - 1, i, tm[i][j]);
				} else {
					cur = 0;
				}

				if (cur >= k) {
					ans = min(ans, get_max(1, 0, n - 1, i - k + 1, i));
				}
			}
		}
	}

	for (int s = 0; s <= 2 * (n - 1); s++) {
		int cur = 0;
		t.assign(4 * n, 0);
		for (int i = (n - 1); i >= n - 1 - s; i--) {
			int j = s - (n - 1) + i;
			if (i < n && j < n && j >= 0 && i >= 0) {
				if (tm[i][j]) {
					cur++;
					update(1, 0, n - 1, i, tm[i][j]);
				} else {
					cur = 0;
				}

				if (cur >= k) {
					ans = min(ans, get_max(1, 0, n - 1, i, i + k - 1));
				}
			}
		}
	}

    if (ans == INT_MAX) cout << 0 << endl;
    else 				cout << ans << endl;
}