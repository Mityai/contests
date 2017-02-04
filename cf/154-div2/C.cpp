#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100;
const int INF = 2e9;

int n;
int a[N];
int r1, c1, r2, c2;

int get(int k) {
  int ans = 0;
  int c = c1;
  {
    int mn = min(c1, a[k]);
    for (int i = min(r1, k) + 1; i < max(r1, k); i++) {
      mn = min(mn, a[i]);
    }
    ans += abs(k - r1);
    c = mn;
  }
  {
    int mn = min(c, a[r2]);
    for (int i = min(k, r2) + 1; i < max(k, r2); i++) {
      mn = min(mn, a[i]);
    }
    ans += abs(k - r2);
    c = mn;
  }
  ans += abs(c - c2);
  return ans;
}

int main() {
#if __APPLE__
#else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }

  scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
  --r1, --r2, --c1, --c2;

  int ans = INF;
  for (int i = 0; i < n; i++) {
    ans = min(ans, get(i));
  }

  printf("%d\n", ans);
}
