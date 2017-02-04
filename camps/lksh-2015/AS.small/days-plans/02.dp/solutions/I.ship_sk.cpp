/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.02.04
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef pair <int, int> pii;

const int N = 10000;

int n, t, a[N];
pii f[2][N + 1];

inline void relax( int i, int j, pii p, int x ) {
	if (p.second + x > t)
		p.first++, p.second = x;
	else
		p.second += x;
	if (f[i][j].first == 0 || f[i][j] > p)
		f[i][j] = p;
}

int main() {
	assert(scanf("%d%d", &t, &n) == 2 && n <= N);
	forn(i, n)
		scanf("%d", &a[i]);
	f[0][n] = {1, 0};

	int ans = n;
	for (int l = 0; l <= n; l++) {
		int c = l & 1;
		memset(f[c ^ 1], 0, sizeof(f[c]));
		for (int r = n; r >= l; r--)
			if (f[c][r].first)
				if (l == r)
					ans = min(ans, f[c][r].first);
				else {
					relax(c ^ 1, r, f[c][r], a[l]);
					relax(c, r - 1, f[c][r], a[r - 1]);
				}
	}
	printf("%d\n", ans);
	return 0;
}
