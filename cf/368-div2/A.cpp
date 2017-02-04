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

  int n, m;
  cin >> n >> m;

  bool ok = false;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      cin >> c;

      ok |= c == 'C';
      ok |= c == 'Y';
      ok |= c == 'M';
    }
  }

  printf("%s\n", ok ? "#Color" : "#Black&White");
}
