/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.07.13
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

const int N = 5e5;

set<int> yes;
struct Event {
  int x, i;
  bool operator < ( Event e ) const { 
    return x < e.x;
  }
};
int en, c[N];
Event e[N];

int main() {
  int k, m;
  scanf("%*d%d%d", &k, &m);
  forn(i, m) {
    int l, r;
    scanf("%d%d%d", &c[i], &l, &r), c[i]--;
    e[en++] = {l, i};
    e[en++] = {r + 1, i};
  }
  sort(e, e + en);

  int last = -1;
  vector<int> ans(k, 0);
  forn(i, en) {
    int id = e[i].i;
    if (yes.size()) 
      ans[c[*yes.rbegin()]] += e[i].x - last;
    last = e[i].x;
    if (yes.count(id))
      yes.erase(id);
    else
      yes.insert(id);
  }
  forn(i, k)
    printf("%d ", ans[i]);
  return 0;
}
