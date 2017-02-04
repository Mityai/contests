#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX - 1234567890;
const ll K = 50;

int main() {
#if __APPLE__
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif

  int n;
  ll k;
  scanf("%d%lld", &n, &k);

  ll a[n + 1], b[n + 1];
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    b[i] = a[i];
  }

  if (k == 1) {
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
      if (a[ans] > a[i]) ans = i;
    }
    printf("1\n%lld\n", ans);
    return 0;
  }

  vector<ll> primes;
  ll v = k;
  for (ll i = 2; i * i <= v; i++) {
    if (v % i == 0) primes.push_back(i);
    while (v % i == 0) v /= i;
  }
  if (v != 1) primes.push_back(v);

  vector<ll> dels;
  dels.push_back(1);
  dels.push_back(k);
  for (ll i = 2; i * i <= k; i++) {
    if (k % i == 0) {
      dels.push_back(i);
      if (i * i != k) dels.push_back(k / i);
    }
  }
  int m = (int)dels.size();
  sort(dels.begin(), dels.end());

  unordered_map<ll, int> to;
  for (int i = 0; i < m; i++) {
    to[dels[i]] = i;
  }

  bool used[m];
  memset(used, 0, sizeof used);
  used[0] = true;

  ll gcd[n + 1][m];
  for (int i = 1; i <= n; i++) for (int j = 0; j < m; j++) gcd[i][j] = 1;

  ll left[n + 1][m];
  for (int i = 0; i < m; i++) {
    for (int j = 1; j <= n; j++) {
      left[j][i] = a[j];
    }
  }

  for (int i = 0; i < m; i++) {
    for (ll p : primes) {
      ll newd = dels[i] * p;
      if (to.find(newd) != to.end()) {
        int f = to[newd];
        if (!used[f]) {
          used[f] = true;
          for (int j = 1; j <= n; j++) {
            gcd[j][f] = gcd[j][i];
            left[j][f] = left[j][i];
            if (left[j][i] % p == 0) {
              gcd[j][f] *= p;
              left[j][f] /= p;
            }
          }
        }
      }
    }
  }

  ll dp[n + 1][m];
  int p[n + 1][m];
  for (int i = 0; i <= n; i++) for (int j = 0; j < m; j++) dp[i][j] = INF;

  dp[0][to[k]] = 0;
  for (int i = 1; i <= n; i++) {
    ll cur = a[i];
    for (int j = 0; j < m; j++) {
      ll div = dels[j];
      ll common = gcd[i][j];
      if (common > 1 && dp[i - 1][j] != INF) {
        ll prev = (dp[i - 1][j] >> K);
        ll cost = ((prev + 1) << K) + cur + (dp[i - 1][j] & ((1LL << K) - 1));
        if (dp[i][to[div / common]] > cost) {
          dp[i][to[div / common]] = cost;
          p[i][to[div / common]] = j;
        }
      }
      if (dp[i][j] > dp[i - 1][j]) {
        dp[i][j] = dp[i - 1][j];
        p[i][j] = j;
      }
    }
  }

  ll ansi = 1;
  for (int i = 1; i <= n; i++) {
    if (dp[ansi][to[1]] > dp[i][to[1]]) {
      ansi = i;
    }
  }

  if (dp[ansi][to[1]] == INF) {
    puts("-1");
  } else {
    int len = (dp[ansi][to[1]] >> K);
    vector<int> ans;
    for (int i = ansi, j = to[1]; i >= 1; i--) {
      if (p[i][j] != j) {
        ans.push_back(i);
        j = p[i][j];
      }
    }
    assert(len == (int)ans.size());
    printf("%d\n", len);
    for (int x : ans) {
      printf("%d ", x);
    }
    puts("");
  }
}
