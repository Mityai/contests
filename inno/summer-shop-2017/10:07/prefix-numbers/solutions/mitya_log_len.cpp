#include <cstdio>
#include <cassert>
#include <algorithm>

bool good(int d, int x, int y, int z) {
	if (d % 2 == 0) d /= 2;
	if (d % 5 == 0) d /= 5;
	if (d == 1) return true;
	if (d == 3 || d == 9) return z % d == 0;
	if (d == 2 || d == 4) return x % d == 0;
	if (d == 7) return y == 0;
	assert(false);
}

int const n = 4 * 7 * 9;
int MOD;

template<int SZ> 
void mul(int a[SZ][SZ], int b[SZ][SZ]) {
	static int c[n][n];
	for (int i = 0; i < SZ; ++i) {
		for (int j = 0; j < SZ; ++j) {
			long long val = 0;
			for (int k = 0; k < SZ; ++k) {
				val += (long long) a[i][k] * b[k][j] % MOD;
			}
			c[i][j] = val % MOD;
		}
	}
	for (int i = 0; i < SZ; ++i) {
		std::copy(c[i], c[i] + SZ, a[i]);
	}
}

int a[n][n], b[n][n];

int main() {
	long long len;
	scanf("%I64d%d", &len, &MOD);
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 7; ++y) {
			for (int z = 0; z < 9; ++z) {
				for (int d = 1; d < 10; ++d) {
					if (good(d, x, y, z)) {
						int q = (10 * x + d) % 4;
						int w = (10 * y + d) % 7;
						int e = (10 * z + d) % 9;
						++a[q + 4 * w + 4 * 7 * e][x + 4 * y + 4 * 7 * z];
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
	    b[i][i] = 1;
	}
	for (; len > 0; len /= 2) {
		if (len % 2 == 1) {
			mul(b, a);
		}
		mul(a, a);
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += b[i][0];
		ans %= MOD;
	}
	printf("%d\n", ans);
}