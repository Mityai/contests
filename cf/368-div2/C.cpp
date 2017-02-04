#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;

int main() {
#if __APPLE__
  //freopen("C.in", "r", stdin);
  //freopen("C.out", "w", stdout);
#endif

  ll n;
  cin >> n;

  if (n <= 2) {
    puts("-1");
  } else if (n % 2 == 0) {
    printf("%lld %lld\n", n * n / 4 + 1, n * n / 4 - 1);
  } else {
    printf("%lld %lld\n", n * n / 2, n * n / 2 + 1);
  }
}
