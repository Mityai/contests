#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  string t = s;
  reverse(t.begin(), t.end());

  cout << s + t << endl;
}
