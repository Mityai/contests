#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);

  int n, m;
  cin >> n >> m;
  if (n > m) {
    int i = 0;
    while (n > 0 && m > 0) {
      if (i & 1) {
        putchar('G');
        m--;
      } else {
        putchar('B');
        n--;
      }
      i++;
    }
    for (i = 0; i < n; i++) {
      putchar('B');
    }
  } else {
    int i = 0;
    while (n > 0 && m > 0) {
      if (i & 1) {
        putchar('B');
        n--;
      } else {
        putchar('G');
        m--;
      }
      i++;
    }
    for (i = 0; i < m; i++) {
      putchar('G');
    }
    for (i = 0; i < n; i++) {
      putchar('B');
    }
  }
}
