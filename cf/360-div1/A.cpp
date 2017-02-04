#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5;

vector<int> g[N];
int col[N];
bool used[N];

void go(int v, int c) {
  used[v] = true;
  col[v] = c;
  for (int u : g[v]) {
    if (!used[u]) {
      go(u, 1 - c);
    }
  }
}

int main() {
#if __APPLE__
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  vector< pair<int, int> > ed(m);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    ed[i] = {a, b};
    g[a].push_back(b);
    g[b].push_back(a);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      go(i, 0);
    }
  }

  for (int i = 0; i < m; i++) {
    int a = ed[i].fi;
    int b = ed[i].se;
    if (col[a] == col[b]) {
      puts("-1");
      return 0;
    }
  }

  int cnt0 = 0, cnt1 = 0;
  for (int i = 0; i < n; i++) {
    if (col[i] == 0) cnt0++;
    else cnt1++;
  }

  printf("%d\n", cnt0);
  for (int i = 0; i < n; i++) {
    if (col[i] == 0) printf("%d ", i + 1);
  }
  puts("");
  printf("%d\n", cnt1);
  for (int i = 0; i < n; i++) {
    if (col[i] == 1) printf("%d ", i + 1);
  }
  puts("");
}
