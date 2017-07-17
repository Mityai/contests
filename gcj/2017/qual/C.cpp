#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

pair<ll, ll> solve(ll n, ll k) {
  map<ll, ll> q;
  q[n] = 1;
  while (true) {
    auto v = --q.end();
    ll len = v->first;
    ll cnt = v->second;
    q.erase(v);

    k -= cnt;

    if (k <= 0) {
      return {len / 2, (len - 1) / 2};
    }

    q[len / 2] += cnt;
    q[(len - 1) / 2] += cnt;
  }
}

pair<ll, ll> stup(ll n, ll k) {
  vector<int> a(n + 2);
  a[0] = a[n + 1] = 1;
  for (int i = 0; i < k; ++i) {
    pair<int, int> best{INT_MIN, INT_MIN};
    int f = 0;
    for (int j = 1; j <= n; ++j) {
      if (a[j] == 0) {
        int lf = 0, rg = 0;
        for (int k = j - 1; k >= 1 && a[k] == 0; --k) {
          ++lf;
        }
        for (int k = j + 1; k <= n && a[k] == 0; ++k) {
          ++rg;
        }
        int mx = max(lf, rg);
        int mn = min(lf, rg);
        pair<int, int> cur{mn, mx};
        if (best < cur) {
          best = cur;
          f = j;
        }
      }
    }
    a[f] = 1;
    if (i == k - 1) {
      swap(best.fi, best.se);
      return best;
    }
  }
}

int main() {
#if __APPLE__
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);

  for (int test = 1; test <= t; ++test) {
    ll n, k;
    scanf("%lld%lld", &n, &k);
    auto ans = solve(n, k);
    printf("Case #%d: %lld %lld\n", test, ans.fi, ans.se);
  }
}
