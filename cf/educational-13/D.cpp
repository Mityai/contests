#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

ll bp(ll x, ll n) {
  if (n == 0) return 1LL;
  ll b = bp(x, n / 2);
  b = (b * b) % MOD;
  if (n & 1) b = (b * x) % MOD;
  return b;
}

int main() {
  ll A, B, n, x;
  cin >> A >> B >> n >> x;

  ll part1 = (bp(A, n) * x) % MOD;
  ll sum = ((bp(A, n) - 1 + MOD) % MOD * bp(A - 1, MOD - 2)) % MOD;
  if (A == 1) sum = n % MOD;
  ll part2 = (B * sum) % MOD;
  ll ans = (part1 + part2) % MOD;

  cout << ans << endl;
}
