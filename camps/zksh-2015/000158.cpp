#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("product.in", "r", stdin);
	freopen("product.out", "w", stdout);	
#endif

	int t;
	scanf("%d", &t);

	for (int ii = 0; ii < t; ii++) {
		int n;
		scanf("%d", &n);
		vector<ll> x(n), y(n);
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x[i]);
		}
		for (int i = 0; i < n; i++) {
			scanf("%lld", &y[i]);
		}

		sort(x.begin(), x.end());
		sort(y.rbegin(), y.rend());
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			ans += x[i] * y[i];
		}
		printf("Case #%d: %lld\n", ii + 1, ans);
	}
}
