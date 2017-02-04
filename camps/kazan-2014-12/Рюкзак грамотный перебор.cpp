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
const int MAXN = 3e5;
const int MAXM = 1e4;
const int MOD = 1e9 + 7;
const double eps = 1e-6;

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("knapsack.in", "r", stdin);
        freopen("knapsack.out", "w", stdout);
    #endif

	int n;
	cin >> n;

	vector<ll> c(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> c[i] >> w[i];
	}

	ll x;
	cin >> x;

	if (n <= 30) {
		int fs = n / 2;
		int ls = n - fs;

		vector<pair<ll, ll> > afs(1 << fs);
		for (int mask = 0; mask < (1 << fs); mask++) {
         	for (int j = 0; j < fs; j++) {
             	if (mask & (1 << j)) {
                 	afs[mask].fi += w[j];
					afs[mask].se += c[j];
				}
			}
		}

		sort(afs.begin(), afs.end());

		ll mx = 0;
		for (int i = 0; i < sz(afs); i++) {
			mx = max(mx, afs[i].se);
			afs[i].se = mx;
		}
		
		ll ans = 0;
		for (int mask = 0; mask < (1 << ls); mask++) {
			ll curw = 0;
			ll curc = 0;
         	for (int j = 0; j < ls; j++) {
				if (mask & (1 << j)) {
                 	curw += w[fs + j];
					curc += c[fs + j];
				}
			}

			int l = 0, r = (1 << fs);
			while (l + 1 < r) {
             	int m = (l + r) / 2;
				if (curw + afs[m].fi <= x) {
					l = m;
				} else {
                 	r = m;
				}
			}

			if (curw + afs[l].fi <= x && ans < afs[l].se + curc) {
             	ans = afs[l].se + curc;
			}
		}
		cout << ans << endl;
	} else {
		vector<vector<ll> > dp(n + 1, vector<ll> (x + 1));
		ll ans = 0;
		for (int i = 1; i <= n; i++) {
         	for (int j = 1; j <= x; j++) {
             	dp[i][j] = dp[i - 1][j];
				if (j >= w[i - 1]) {
                 	dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i - 1]] + c[i - 1]);
					ans = max(ans, dp[i][j]);
				}
			}
		}
		cout << ans << endl;
	}
}
