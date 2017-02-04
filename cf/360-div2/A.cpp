#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, d;
  cin >> n >> d;

  string X(n, '1');

  int last = -1;
  int ans = 0;
  for (int i = 0; i < d; i++) {
    string s;
    cin >> s;

    if (s == X) {
      last = i;
    } else {
      ans = max(ans, i - last);
    }
  }

  cout << ans << endl;
}
