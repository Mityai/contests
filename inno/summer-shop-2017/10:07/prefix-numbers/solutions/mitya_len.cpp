#include <cstdio>
#include <cassert>

#define xyz for (int x = 0; x < 4; ++x) for (int y = 0; y < 7; ++y) for (int z = 0; z < 9; ++z)

bool good(int d, int x, int y, int z) {
	if (d % 2 == 0) d /= 2;
	if (d % 5 == 0) d /= 5;
	if (d == 1) return true;
	if (d == 3 || d == 9) return z % d == 0;
	if (d == 2 || d == 4) return x % d == 0;
	if (d == 7) return y == 0;
	assert(false);
}

int MOD;

void add(int& a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int dp[4][7][9];
int to[4][7][9];

int main() {
	dp[0][0][0] = 1;
	int needLen;
	scanf("%d%d", &needLen, &MOD);
	for (int len = 1; len <= needLen; ++len) {
		xyz to[x][y][z] = 0;
		xyz {
			for (int d = 1; d < 10; ++d) {
				if (good(d, x, y, z)) {
					add(to[(10 * x + d) % 4][(10 * y + d) % 7][(10 * z + d) % 9], dp[x][y][z]);
				}
			}
		}
		xyz dp[x][y][z] = to[x][y][z];
	}
	int ans = 0;
	xyz add(ans, dp[x][y][z]);
	printf("%d\n", ans);
}