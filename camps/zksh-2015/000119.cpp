#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	//freopen("paths.in", "r", stdin);
	//freopen("paths.out", "w", stdout);
#endif

	int n;
	scanf("%d", &n);

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	sort(a.begin(), a.end());


	ll g = a[1] - a[0];
	for (int i = 2; i < n; i++) {
		g = gcd(g, a[i] - a[i - 1]);
	}

	vector<ll> ans;
	for (ll i = 1; i * i <= g; i++) {
		if (g % i == 0) {
			if (i > 1)
			ans.push_back(i);
			if (i * i != g) {
				if (g / i > 1)
				ans.push_back(g / i);
			}
		}
	}

	cout << (int)ans.size() << endl;
	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i] << endl;
	}
}
