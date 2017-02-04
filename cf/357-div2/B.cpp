#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);

  const ll A = 1234567;
  const ll B = 123456;
  const ll C = 1234;

  for (ll i = 0; A * i <= n; i++) {
    for (ll j = 0; A * i + B * j <= n; j++) {
      if ((n - A * i - B * j) % C == 0) {
        puts("YES");
        return 0;
      }
    }
  }

  puts("NO");
}
