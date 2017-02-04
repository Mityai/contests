#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

ll cub(ll n) {
  ll lb = 0, rb = 1;
  while (rb * rb * rb <= n) rb *= 2;
  while (lb + 1 < rb) {
    ll mb = (lb + rb) / 2;
    if (mb * mb * mb <= n) lb = mb;
    else rb = mb;
  }
  return lb;
}

ll cnt(ll n) {
  ll k = cub(n);
  ll sum = 0;
  for (; k > 1; k--) {
    ll f = k * k * k;
    sum += n / f;
  }
  return sum;
}

int main() {
#if __APPLE__
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif

  ll m;
  while (scanf("%lld", &m) == 1) {
    ll lb = 0, rb = 1;
    while (cnt(rb) < m) rb *= 2;
    while (lb + 1 < rb) {
      ll mb = (lb + rb) / 2;
      ll n = mb;
      ll sum = cnt(n);
      if (sum >= m) rb = mb;
      else lb = mb;
    }
    if (cnt(rb) == m) {
      printf("%lld\n", rb);
    } else {
      puts("-1");
    }
  }
}
