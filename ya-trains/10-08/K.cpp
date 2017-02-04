#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;


int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<ll> a(n + 1), dp(n + 1), sum(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = s[i - 1] - '0';
    }
    dp[0] = 0;
    sum[0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i] = ((dp[i - 1] * 10) % MOD + (sum[i - 1] * a[i]) % MOD) % MOD;
        sum[i] = (sum[i - 1] + dp[i]) % MOD;
    }
    cout << dp[n];
}
