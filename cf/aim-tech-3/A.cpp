#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

char prev(char c) {
  if (c == 'a') return 'z';
  return --c;
}

int main() {
#if __APPLE__
#endif

  string s;
  cin >> s;

  int start = 0;
  string t = s;
  for (int i = 0; i < s.length(); i++) {
    if (start == 1) {
      if (prev(s[i]) < s[i]) t[i] = prev(s[i]);
      else start = 2;
    } else if (start == 0) {
      if (prev(s[i]) < s[i]) t[i] = prev(s[i]), start = 1;
    }
  }
  if (start == 0) {
    t.back() = prev(t.back());
  }

  cout << t << endl;
}
