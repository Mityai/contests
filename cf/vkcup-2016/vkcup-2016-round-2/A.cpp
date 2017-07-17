#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  freopen("A.in", "r", stdin);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    string s;
    cin >> s;

    s = "#" + s;

    bool used[n + 1];
    memset(used, 0, sizeof used);

    int d[n + 1];
    for (int i = 1; i <= n; i++) {
      scanf("%d", d + i);
    }

    int pos = 1;
    bool ok = false;
    while (!used[pos]) {
      used[pos] = true;
      if (s[pos] == '<') {
        pos -= d[pos];
      } else {
        pos += d[pos];
      }

      if (pos <= 0 || pos > n) {
        ok = true;
        break;
      }
    }

    if (ok) {
      puts("FINITE");
    } else {
      puts("INFINITE");
    }
  }
}
