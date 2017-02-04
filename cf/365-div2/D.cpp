#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int n;

int getxor(int x, int *f) {
  int ret = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
    ret ^= f[i];
  }
  return ret;
}

int que(int l, int r, int *f) {
  int ret = getxor(r, f);
  if (l - 1 >= 0) ret ^= getxor(l - 1, f);
  return ret;
}

void add(int x, int val, int *f) {
  for (int i = x; i < n; i = i | (i + 1)) {
    f[i] ^= val;
  }
}

int main() {
#if __APPLE__
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif

  while (scanf("%d", &n) == 1) {
    int a[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    int pref[n];
    for (int i = 0; i < n; i++) {
      pref[i] = a[i];
      if (i > 0) pref[i] ^= pref[i - 1];
    }

    int fenw[n];
    memset(fenw, 0, sizeof fenw);

    int q;
    scanf("%d", &q);

    vector< vector< pair<int, int> > > g(n);
    for (int i = 0; i < q; i++) {
      int l, r;
      scanf("%d%d", &l, &r);
      --r, --l;
      g[r].push_back({l, i});
    }

    int ans[q];

    map<int, int> last;
    for (int i = 0; i < n; i++) {
      if (last.find(a[i]) == last.end()) {
        last[a[i]] = i;
        add(i, a[i], fenw);
      } else {
        add(last[a[i]], a[i], fenw);
        last[a[i]] = i;
        add(i, a[i], fenw);
      }
      for (auto v : g[i]) {
        int l = v.fi, r = i, id = v.se;
        int res = pref[r];
        if (l - 1 >= 0) res ^= pref[l - 1];
        res ^= que(l, r, fenw);
        ans[id] = res;
      }
    }

    for (int i = 0; i < q; i++) {
      printf("%d\n", ans[i]);
    }
  }
}
