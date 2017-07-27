#include <cstdio>

bool good(long long x) {
	if (x == 0) return true;
	int d = x % 10;
	if (d == 0) return false;
	return x % d == 0 && good(x / 10);
}

int main() {
	int len, MOD;
	scanf("%d%d", &len, &MOD);
	long long from = 1;
	for (int i = 0; i < len - 1; ++i) from *= 10;
	int ans = 0;
	for (long long x = from; x < 10 * from; ++x) {
		if (good(x)) {
			++ans;
			ans %= MOD;
		}
	}
	printf("%d\n", ans);
}