#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  //freopen("B.in", "r", stdin); freopen("B.out", "w", stdout);
#endif

  int n, k;
  scanf("%d%d", &n, &k);

  vector<int> p;
  for (ll i = 2; i * i <= k; i++) {
    if (k % i == 0) {
      int s = 1;
      while (k % i == 0) {
        k /= i;
        s *= i;
      }
      p.push_back(s);
    }
  }
  if (k != 1) {
    p.push_back(k);
  }

  int m = p.size();
  bool ok[m];
  memset(ok, false, sizeof ok);

  for (int i = 0; i < n; i++) {
    int c;
    scanf("%d", &c);
    for (int j = 0; j < m; j++) {
      if (c % p[j] == 0) {
        ok[j] = true;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    if (!ok[i]) {
      puts("No");
      return 0;
    }
  }

  puts("Yes");
}
