#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int LAST16 = (1 << 16) - 1;
const int LAST17 = (1 << 17) - 1;

int bin_pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = (res * 1ll * a) % MOD;
        a = (a * 1ll * a) % MOD;
        n >>= 1;
    }
    return res;
}

int get_bits(int x) {
    int ret = 1;
    for (int i = 0; i < x - 1; ++i) ret <<= 1;
    return ret;
}

int sum(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int x, y, z;

bool ok(int bits) {
    int t = 0, sum = 0;
    int cur = 0;
    while (bits > 0) {
        if ((bits & 1) == 0) ++cur;
        else {
            ++cur;
            sum += cur;
            cur = 0;
            if (t == 0) {
                if (sum == z) sum = 0, t = 1;
            } else if (t == 1) {
                if (sum == y) sum = 0, t = 2;
            } else if (t == 2) {
                if (sum == x) {
                    sum = 0, t = 3;
                    break;
                }
            }
        }
        bits >>= 1;
    }
    return t != 3;
}

int main() {
    int n;
    scanf("%d%d%d%d", &n, &x, &y, &z);

    vector<vector<int>> dp(n + 1, vector<int>(1 << 16));
    dp[0][0] = 1;
    for (int len = 1; len <= n; ++len) {
        for (int prev = 0; prev < (1 << 16); ++prev) {
            for (int cur = 1; cur <= 10; ++cur) {
                int bits = get_bits(cur);
                int cur_bits = (prev << cur) | bits;
                cur_bits &= LAST17;
                if (ok(cur_bits)) {
                    cur_bits &= LAST16;
                    dp[len][cur_bits] = sum(dp[len][cur_bits], dp[len - 1][prev]);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < (1 << 16); ++i) {
        ans = sum(ans, dp[n][i]);
    }

    ans = sub(bin_pow(10, n), ans);
    printf("%d\n", ans);
}
