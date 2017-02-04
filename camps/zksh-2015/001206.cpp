#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int n, m;
vector<vector<ll> > d;
void go(int i, int j, int mask, int newmask) {
	if (j == m) {
		d[i + 1][newmask] += d[i][mask];
		return;
	}

	int curmask = (1 << j);
	if (mask & curmask) {
		go(i, j + 1, mask, newmask);
	} else {
		go(i, j + 1, mask, newmask | curmask);
		if (j + 1 < m && !(mask & (curmask << 1))) {
			go(i, j + 2, mask, newmask);
		} 
	}
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("dominoes.in", "r", stdin);
	freopen("dominoes.out", "w", stdout);	
#endif

	scanf("%d%d", &n, &m);
	if (m > n) swap(n, m);

	int x = (4 << 1);

	d.resize(n + 1, vector<ll> (1 << m));
	d[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int mask = 0; mask < (1 << m); mask++) {
			go(i, 0, mask, 0);
		}
	}

	printf("%lld\n", d[n][0]);
}
