#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

bool cmp(pair<pair<ll, ll>, int> a, pair<pair<ll, ll>, int> b) {
	return a.fi.fi + a.fi.se > b.fi.fi + b.fi.se;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("dwarfs.in", "r", stdin);
	freopen("dwarfs.out", "w", stdout);	
#endif

	int n;
	scanf("%d", &n);

	ll suma = 0;
	vector<pair<pair<ll, ll>, int> > a(n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i].fi.fi);
		a[i].se = i + 1;
		suma += a[i].fi.fi;
	}
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i].fi.se);
	}

	sort(a.begin(), a.end(), cmp);

	ll t = 0;
	for (int i = 0; i < n; i++) {
		t += a[i].fi.fi;
		if (t + a[i].fi.se <= suma) {
			puts("-1");
			return 0;
		}
	}

	for (int i = 0; i < n; i++) {
		cout << a[i].se << ' ';
	}
}
