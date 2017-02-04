#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  //freopen("A.in", "r", stdin);
  //freopen("A.out", "w", stdout);
#endif

  int n;
  cin >> n;

  int a = 0, b = 0;
  for (int i = 0; i < n; i++) {
    int m, c;
    cin >> m >> c;
    if (m > c) a++;
    else if (c > m) b++;
  }

  if (a > b) {
    puts("Mishka");
  } else if (b > a) {
    puts("Chris");
  } else {
    puts("Friendship is magic!^^");
  }
}
