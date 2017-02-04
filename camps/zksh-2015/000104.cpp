#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);	
#endif

	ll n;
	scanf("%lld", &n);

	vector<pair<ll, ll> > a(n);
	for (int i = 0; i < n; i++) {
     	scanf("%lld%lld", &a[i].fi, &a[i].se);
	}

	vector<vector<ll> > dp(n, vector<ll> (2));
	dp[0][0] = a[0].fi + 2 * (a[0].se - a[0].fi) - 1;
	dp[0][1] = a[0].se - 1;
	for (int i = 1; i < n; i++) {
		int dist = a[i].se - a[i].fi;
		dp[i][0] = min(dp[i - 1][0] + abs(a[i - 1].fi - a[i].fi) + 2 * dist,
					   dp[i - 1][0] + abs(a[i - 1].fi - a[i].se) + dist);
		dp[i][0] = min(dp[i][0],
				   min(dp[i - 1][1] + abs(a[i - 1].se - a[i].fi) + 2 * dist,
					   dp[i - 1][1] + abs(a[i - 1].se - a[i].se) + dist));

		dp[i][1] = min(dp[i - 1][0] + abs(a[i - 1].fi - a[i].fi) + dist,
					   dp[i - 1][0] + abs(a[i - 1].fi - a[i].se) + 2 * dist);
		dp[i][1] = min(dp[i][1],
				   min(dp[i - 1][1] + abs(a[i - 1].se - a[i].fi) + dist,
					   dp[i - 1][1] + abs(a[i - 1].se - a[i].se) + 2 * dist));
	}

	ll ans = min(dp[n - 1][0] + n - a[n - 1].fi, dp[n - 1][1] + n - a[n - 1].se);
	cout << ans + n - 1 << endl;
}
