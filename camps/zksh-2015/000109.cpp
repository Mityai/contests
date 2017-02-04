#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

bool cmp(pair<double, double> a, pair<double, double> b) {
	return a.fi / a.se > b.fi / b.se;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("dust.in", "r", stdin);
	freopen("dust.out", "w", stdout);	
#endif

	int n;
	double w;
	cin >> n >> w;

	vector<pair<double, double> > a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].fi >> a[i].se;
	}

	sort(a.begin(), a.end(), cmp);

	double curw = 0;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		if (curw >= w) break;
		if (curw + a[i].se <= w) {
			ans += a[i].fi;
			curw += a[i].se;
		} else {
			ans += a[i].fi * (w - curw) / a[i].se;
			break;
		}
	}

	printf("%.6lf\n", ans);
}
