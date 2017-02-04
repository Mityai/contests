#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
#endif

  int n;
  scanf("%d", &n);

  ll a[n];
  for (int i = 0; i < n; i++) {
    scanf("%lld", a + i);
  }
  sort(a, a + n);

  ll lb = a[0], rb = a[n - 1];
  while (lb + 2 < rb) {
    ll mb1 = (lb + lb + rb) / 3;
    ll mb2 = (lb + rb + rb) / 3;
    ll f1 = 0, f2 = 0;
    for (int i = 0; i < n; i++) {
      f1 += abs(a[i] - mb1);
      f2 += abs(a[i] - mb2);
    }
    if (f1 <= f2) {
      rb = mb2;
    } else {
      lb = mb1;
    }
  }

  ll ans = LLONG_MAX, ansp = lb;
  for (ll mb = lb; mb <= rb; mb++) {
    ll f = 0;
    for (int i = 0; i < n; i++) {
      f += abs(a[i] - mb);
    }
    if (ans > f) {
      ans = f;
      ansp = mb;
    }
  }

  printf("%lld\n", ansp);
}
