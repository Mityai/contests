#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX - 1234567890;

bool check(string &s, string &t) {
  for (int i = 0; i < (int)min(s.length(), t.length()); i++) {
    if (s[i] < t[i]) return true;
    if (s[i] > t[i]) return false;
  }
  if (s.length() > t.length()) return false;
  return true;
}

int main() {
#if __APPLE__
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    int c[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", c + i);
    }

    vector<string> a(n), b(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      b[i] = a[i];
      reverse(b[i].begin(), b[i].end());
    }

    ll dp[n][2];
    for (int i = 0; i < n; i++) dp[i][0] = dp[i][1] = INF;

    dp[0][0] = 0;
    dp[0][1] = c[0];

    for (int i = 1; i < n; i++) {
      if (check(a[i - 1], a[i])) {
        dp[i][0] = min(dp[i][0], dp[i - 1][0]);
      }
      if (check(b[i - 1], a[i])) {
        dp[i][0] = min(dp[i][0], dp[i - 1][1]);
      }

      if (check(a[i - 1], b[i])) {
        dp[i][1] = min(dp[i][1], dp[i - 1][0] + c[i]);
      }
      if (check(b[i - 1], b[i])) {
        dp[i][1] = min(dp[i][1], dp[i - 1][1] + c[i]);
      }
    }

    ll ans = min(dp[n - 1][0], dp[n - 1][1]);
    if (ans == INF) {
      puts("-1");
    } else {
      printf("%lld\n", ans);
    }
  }
}
