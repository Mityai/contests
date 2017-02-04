#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 3e5;

int n, m;
vector<int> g[N];
int centroid[N], sz[N], p[N], depth[N];
bool leaf[N], used[N];

void calcsz(int v, int d = 0) {
  sz[v] = 1;
  depth[v] = d;
  for (int u : g[v]) {
    calcsz(u, d + 1);
    sz[v] += sz[u];
  }
}

int main() {
  scanf("%d%d", &n, &m);

  memset(leaf, true, n * sizeof(leaf[0]));
  for (int i = 1; i < n; i++) {
    int x;
    scanf("%d", &x);
    --x;
    p[i] = x;
    g[x].push_back(i);
    leaf[x] = false;
  }

  calcsz(0);
  vector< pair<int, int> > s;
  for (int i = 0; i < n; i++) {
    s.push_back({depth[i], i});
  }
  sort(s.rbegin(), s.rend());

  queue<int> q;
  for (int i = 0; i < n; i++) {
    q.push(s[i].se);
  }

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    int W = sz[v];
    bool iscentroid = true;
    for (int u : g[v]) {
      if (2 * sz[u] > W) {
        iscentroid = false;
        break;
      }
    }

    if (iscentroid) {
      centroid[v] = v;
    } else {
      for (int u : g[v]) {
        int cur_centroid = centroid[u];
        bool ok = false;
        while (cur_centroid != v) {
          int szup = W - sz[cur_centroid];
          if (2 * szup <= W) {
            centroid[v] = cur_centroid;
            ok = true;
            break;
          }
          cur_centroid = p[cur_centroid];
        }
        if (ok) break;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    int v;
    scanf("%d", &v);
    printf("%d\n", centroid[v - 1] + 1);
  }
}
