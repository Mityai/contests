#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

bool cmp(pair<ll, ll> a, pair<ll, ll> b) {
	return a.fi + a.se < b.fi + b.se;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("boxes.in", "r", stdin);
	freopen("boxes.out", "w", stdout);	
#endif

	int n;
	scanf("%d", &n);

	vector<pair<ll, ll> > a(n);
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", &a[i].fi, &a[i].se);
	}

	sort(a.begin(), a.end(), cmp);

	ll W = 0;
	auto cmp1 = [](pair<ll, ll> a, pair<ll, ll> b) { return a.fi > b.fi || (a.fi == b.fi && a.se < b.se); };
	multiset<pair<ll, ll>, decltype(cmp1)> q(cmp1);
	for (int i = 0; i < n; i++) {
		if (a[i].se >= W) {
			W += a[i].fi;
			q.insert(a[i]);
		} else {
			ll mx = q.begin()->fi;
			if (a[i].se >= W - mx && a[i].fi < mx) {
				W -= mx;
				q.erase(q.begin());
				W += a[i].fi;
				q.insert(a[i]);
			}
		}
	}

	cout << (int)q.size() << endl;
}
