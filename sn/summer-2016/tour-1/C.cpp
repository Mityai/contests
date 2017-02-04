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

  int t;
  scanf("%d", &t);

  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    int st = n;

    if (m > n) puts("NO");
    else {
      n--;
      n /= 2;
      int f = n * 2 + 1;
      if (n % 2 == 0) {
        if (m % 2 == 1) {
          puts("YES");
        } else {
          puts("NO");
        }
      } else {
        if (m % 2 == 0) {
          puts("YES");
        } else {
          puts("NO");
        }
      }
    }
  }
}
