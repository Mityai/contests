#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX - 123457890;

bool cmp(pair<ll, ll> a, pair<ll, ll> b) {
	return a.se < b.se;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	//freopen("boxes.in", "r", stdin);
	//freopen("boxes.out", "w", stdout);	
#endif

	int n;
	scanf("%d", &n);

	vector<pair<ll, ll> > a(n + 1);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i].fi);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i].se);
	}

	sort(a.begin() + 1, a.end(), cmp);

	vector<vector<ll> > dp(n + 1, vector<ll> (n + 1, INF));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i - 1; j++) {
			dp[i][j] = min(dp[i][j], dp[i - 1][j]);
			if (dp[i - 1][j] + a[i].fi <= a[i].se) {
				dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + a[i].fi);
			}
		}
	}

	for (int i = n; i >= 0; i--) {
		if (dp[n][i] != INF) {
			cout << i << endl;
			return 0;
		}
	}
}
