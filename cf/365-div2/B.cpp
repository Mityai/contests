#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {

    ll c[n];
    ll sumc = 0;
    for (int i = 0; i < n; i++) {
      scanf("%lld", c + i);
      sumc += c[i];
    }

    bool is[n];
    memset(is, 0, sizeof is);

    for (int i = 0; i < k; i++) {
      int x;
      scanf("%d", &x);
      --x;
      is[x] = true;
    }

    ll sm[n];
    memset(sm, 0, sizeof sm);
    
    for (int i = 0; i < n; i++) {
      sm[i] = is[i] * c[i];
      if (i > 0) {
        sm[i] += sm[i - 1];
      }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
      int prev = (i - 1 + n) % n;
      if (is[i]) {
        ans += (sumc - c[prev] * (1 - is[prev]) - sm[i]) * c[i];
      } else {
        ans += c[(i + 1) % n] * c[i];
      }
    }

    printf("%lld\n", ans);
  }
}
