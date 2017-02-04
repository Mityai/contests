#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
  int n, q;
  scanf("%d%d", &n, &q);

  int col[q];
  memset(col, 0, sizeof col);

  int maxt = 0;
  int cnt = 0;
  map<int, int> unread;
  map<int, int> pos;
  int ans = 0;
  for (int i = 0; i < q; i++) {
    int t, x;
    scanf("%d%d", &t, &x);
    if (t == 1) {
      col[cnt++] = x;
      unread[x]++;
      ans++;
    } else if (t == 2) {
      ans -= unread[x];
      unread[x] = 0;
      pos[x] = cnt;
    } else {
      for (int j = maxt; j < x; j++) {
        if (j < pos[col[j]]) col[j] = 0;
        else {
          unread[col[j]]--;
          ans--;
        }
      }
      maxt = max(maxt, x);
    }
    printf("%d\n", ans);
  }
}
