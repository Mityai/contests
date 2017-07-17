#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif

  ios_base::sync_with_stdio(false);

  int t;
  cin >> t;

  for (int test = 1; test <= t; ++test) {
    string s;
    int k;
    cin >> s >> k;

    int cnt = 0;
    for (int i = 0; i + k <= s.length(); ++i) {
      if (s[i] == '-') {
        ++cnt;
        for (int j = i; j < i + k; ++j) {
          if (s[j] == '-') {
            s[j] = '+';
          } else {
            s[j] = '-';
          }
        }
      }
    }

    bool ok = true;
    for (int i = 0; i < s.length(); ++i) {
      if (s[i] != '+') {
        ok = false;
        break;
      }
    }

    printf("Case #%d: ", test);
    if (ok) {
      printf("%d\n", cnt);
    } else {
      puts("IMPOSSIBLE");
    }
  }
}
