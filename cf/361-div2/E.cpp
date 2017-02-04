#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int N = 2e5 + 1;

ll fact[N];

ll bp(ll x, ll n) {
  if (n == 0) return 1LL;
  ll b = bp(x, n / 2);
  b = (b * b) % MOD;
  if (n & 1) b = (b * x) % MOD;
  return b;
}

ll cnk(ll n, ll k) {
  if (k < 0 || k > n) return 0;
  ll m = (fact[n] * bp(fact[k], MOD - 2)) % MOD;
  m = (m * bp(fact[n - k], MOD - 2)) % MOD;
  return m;
}

int main() {
  fact[0] = 1;
  for (ll i = 1; i < N; i++) {
    fact[i] = (fact[i - 1] * i) % MOD;
  }

  int n, k;
  scanf("%d%d", &n, &k);

  vector<int> op(n), cl(n);
  vector<int> all;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &op[i], &cl[i]);
    all.push_back(op[i]);
    all.push_back(cl[i]);
  }

  sort(all.begin(), all.end());
  all.erase(unique(all.begin(), all.end()), all.end());

  vector<int> hp;
  for (int i = 1; i < (int)all.size(); i++) {
    if (all[i] - all[i - 1] >= 2) hp.push_back(all[i] - 1);
  }
  int m = hp.size();

  for (int x : hp) all.push_back(x);
  sort(all.begin(), all.end());

  sort(op.begin(), op.end());
  sort(cl.begin(), cl.end());

  ll ans = 0;
  int i = 0, j = 0, z = 0;
  int cnt = 0;
  for (int cur : all) {
    while (i < n && op[i] <= cur) i++, cnt++;
    ans = (ans + cnk(cnt, k)) % MOD;
    while (j < n && cl[j] <= cur) j++, cnt--;
    while (z < m && hp[z] < cur) z++;
    if (z < m && hp[z] == cur) {
      int prev = max(op[i - 1], (j == 0 ? op[i - 1] : cl[j - 1]));
      ans = (ans + (hp[z] - prev - 1) * cnk(cnt, k)) % MOD;
    }
  }

  printf("%lld\n", ans);
}
