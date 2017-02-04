#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5;

vector<int> g[N];
int p[N];
bool leaf[N];
bool root[N];
int lvl[N];

void dfs(int v, int d) {
  lvl[v] = d;
  for (int u : g[v]) {
    dfs(u, d + 1);
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  memset(leaf, true, sizeof leaf);
  memset(root, true, sizeof root);
  memset(p, -1, sizeof p);

  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    p[b] = a;
    leaf[a] = false;
    root[b] = false;
  }

  int a[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
    --a[i];
  }

  for (int i = 0; i < n; i++) {
    if (root[i]) dfs(i, 0);
  }

  vector< pair<int, int> > w;
  for (int i = 0; i < n; i++) {
    w.push_back({lvl[i], i});
  }
  sort(w.rbegin(), w.rend());

  vector<int> ans;
  for (auto s : w) {
    int v = s.se;
    if (a[v] == v) {
      ans.push_back(v);
    }
    if (p[v] != -1) {
      if (a[v] != v && a[p[v]] != a[v]) {
        puts("-1");
        return 0;
      }
    }
  }

  printf("%d\n", (int)ans.size());
  for (int x : ans) {
    printf("%d\n", x + 1);
  }
  puts("");
}
