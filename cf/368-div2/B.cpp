#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
#endif

  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  vector<int> u(m), v(m), l(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &u[i], &v[i], &l[i]);
    --u[i], --v[i];
  }

  bool is[n];
  memset(is, 0, sizeof is);
  for (int i = 0; i < k; i++) {
    int x;
    scanf("%d", &x);
    is[x - 1] = true;
  }

  int ans = INT_MAX;
  for (int i = 0; i < m; i++) {
    if (is[v[i]] + is[u[i]] == 1) {
      ans = min(ans, l[i]);
    }
  }

  if (ans == INT_MAX) {
    puts("-1");
  } else {
    printf("%d\n", ans);
  }
}
