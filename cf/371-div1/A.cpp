#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int K = 18;

int main() {
#if __APPLE__
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);

  map<ll, int> q;
  for (int i = 0; i < t; i++) {
    char c;
    ll x;
    scanf(" %c %lld", &c, &x);

    ll res = 0;
    for (ll j = 0, t = 1; j < K; j++) {
      ll bit = (x % 10) & 1;
      x /= 10;
      res += bit * t;
      t *= 10LL;
    }

    if (c == '+') {
      q[res]++;
    } else if (c == '-') {
      q[res]--;
    } else {
      printf("%d\n", q[res]);
    }
  }
}
