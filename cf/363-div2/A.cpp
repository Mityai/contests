#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1234567890;

int main() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  int x[n];
  for (int i = 0; i < n; i++) {
    cin >> x[i];
  }

  int ans = INF;
  for (int i = 1; i < n; i++) {
    if (s[i - 1] == 'R' && s[i] == 'L') {
      ans = min(ans, (x[i] - x[i - 1]) / 2);
    }
  }

  if (ans == INF) {
    puts("-1");
  } else {
    printf("%d\n", ans);
  }
}
