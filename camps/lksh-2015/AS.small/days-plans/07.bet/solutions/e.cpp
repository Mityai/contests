/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.13
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n;
  multiset<int> t;
  scanf("%d ", &n);
  forn(i, n) {
    char s[99];
    gets(s);
    if (s[0] == 'I') {
      int x;
      sscanf(s, "Insert(%d)", &x);
      t.insert(x);
    } else {
      int res = (s[4] == 'i' ? *t.begin() : *t.rbegin());
      printf("%d\n", res);
      t.erase(t.find(res));
    }
  }
  return 0;
}
