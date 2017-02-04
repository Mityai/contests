#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  string s[2] = {"I hate", "I love"};
  string t[2] = {"that ", "it\n"};
  for (int i = 0; i < n; i++) {
    cout << s[i & 1] << ' ' << t[i == n - 1];
  }
}
