#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
#endif

  int n;
  cin >> n;

  int a[n][n];
  memset(a, 0, sizeof a);

  int p = 1;
  for (int i = 0, j = n / 2; i <= n / 2; i++, j--) {
    for (int k = j; k < n - j; k++) {
      a[i][k] = p;
      p += 2;
    }
  }
  for (int i = n - 1, j = n / 2; i > n / 2; i--, j--) {
    for (int k = j; k < n - j; k++) {
      a[i][k] = p;
      p += 2;
    }
  }

  p = 2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (a[i][j] == 0) {
        a[i][j] = p;
        p += 2;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << a[i][j] << ' ';
    }
    cout << endl;
  }
}
