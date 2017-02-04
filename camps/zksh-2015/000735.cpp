#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

struct Work {
	ll a, b, i;
};

bool cmp(Work w1, Work w2) {
	return min(w2.a, w1.b) > min(w2.b, w1.a);
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("f2cmax.in", "r", stdin);
	freopen("f2cmax.out", "w", stdout);	
#endif

	int n;
	scanf("%d", &n);
	vector<Work> w(n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &w[i].a);
		w[i].i = i + 1;
	}
	for (int i = 0; i < n; i++) {
		scanf("%lld", &w[i].b);
	}

	sort(w.begin(), w.end(), cmp);
	ll t = 0;
	vector<ll> st(n);
	for (int i = 0; i < n; i++) {
		t += w[i].a;
		if (i > 0){
			st[i] = max(st[i - 1] + w[i - 1].b, t);
		} else {
			st[i] = t;
		}
	}
	cout << st[n - 1] + w[n - 1].b << endl;
	for (int i = 0; i < n; i++) {
		printf("%lld ", w[i].i);
	}
	puts("");
	for (int i = 0; i < n; i++) {
		printf("%lld ", w[i].i);
	}
	puts("");
}
