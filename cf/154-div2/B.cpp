#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
#else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  int a[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }

  sort(a, a + n);

  int ans = n;
  for (int i = 0; i < n; i++) {
    int lb = i, rb = n;
    while (lb + 1 < rb) {
      int mb = (lb + rb) / 2;
      if (a[i] * 2 >= a[mb]) lb = mb;
      else rb = mb;
    }
    ans = min(ans, i + n - rb);
  }

  printf("%d\n", ans);
}
