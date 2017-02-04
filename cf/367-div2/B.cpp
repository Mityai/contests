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

  int n;
  scanf("%d", &n);

  int x[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", x + i);
  }
  sort(x, x + n);

  int q;
  scanf("%d", &q);

  for (int i = 0; i < q; i++) {
    int y;
    scanf("%d", &y);

    printf("%d\n", (int)(upper_bound(x, x + n, y) - x));
  }
}
