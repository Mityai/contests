#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;


int main() {
#if __APPLE__
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    int a[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", a + i);
      --a[i];
    }

    int ans[n];
    memset(ans, 127, sizeof ans);

    queue<int> q;
    q.push(0);
    ans[0] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();

      if (ans[a[v]] > ans[v] + 1) {
        ans[a[v]] = ans[v] + 1;
        q.push(a[v]);
      }
      if (v - 1 >= 0 && ans[v - 1] > ans[v] + 1) {
        ans[v - 1] = ans[v] + 1;
        q.push(v - 1);
      }
      if (v + 1 < n && ans[v + 1] > ans[v] + 1) {
        ans[v + 1] = ans[v] + 1;
        q.push(v + 1);
      }
    }

    for (int i = 0; i < n; i++) {
      printf("%d ", ans[i]);
    }
    puts("");
  }
}
