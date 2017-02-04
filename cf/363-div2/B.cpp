#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int n, m;
  cin >> n >> m;

  vector<string> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  map<int, int> x, y;
  int all = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '*') {
        x[i]++;
        y[j]++;
        all++;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int cnt = x[i] + y[j] - (a[i][j] == '*');
      if (cnt == all) {
        printf("YES\n%d %d\n", i + 1, j + 1);
        return 0;
      }
    }
  }

  puts("NO");
}
