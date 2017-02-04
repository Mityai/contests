#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int n;
  scanf("%d", &n);

  ll a[n];
  for (int i = 0; i < n; i++) {
    scanf("%lld", a + i);
  }

  sort(a, a + n);

  ll sum = 0;
  for (int i = 0; i < n - 1; i++) {
    sum += a[i];
  }

  ll ans = a[n - 1] - sum + 1;
  printf("%lld\n", ans);
}
