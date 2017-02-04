#include <bits/stdc++.h>
using namespace std;

int len(int x) {
  if (x == 0) return 1;
  int ret = 0;
  while (x > 0) ret++, x /= 7;
  return ret;
}

string tostr(int x, int len) {
  if (x == 0) return string(len, '0');
  string ret = "";
  while (x > 0) {
    ret += char((x % 7) + '0');
    x /= 7;
  }
  while (ret.length() < len) {
    ret += "0";
  }
  return ret;
}

int main() {
  int n, m;
  cin >> n >> m;

  --n, --m;
  int lenN = len(n);
  int lenM = len(m);
  int cnt = lenN + lenM;
  if (cnt > 7) puts("0");
  else {
    int ans = 0;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        string H = tostr(i, lenN);
        string M = tostr(j, lenM);
        H += M;
        bool used[7];
        memset(used, 0, sizeof used);
        bool ok = true;
        for (char c : H) {
          int x = c - '0';
          if (used[x]) {
            ok = false;
            break;
          }
          used[x] = true;
        }
        ans += ok;
      }
    }
    printf("%d\n", ans);
  }
}
