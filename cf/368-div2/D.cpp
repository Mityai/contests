#include <bits/stdc++.h>
#define find asdsafl
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e3;
const int S = 1e5;

struct Q {
  int t, u, i, j;

  Q() {}
  Q(int t, int u, int i, int j) : t(t), u(u), i(i), j(j) {}
};

int n, m;
int a[N][N];
int ans[S + 1], sum[N + 1];
bool inv[N + 1];
vector<Q> g[S + 1];

void go(int v, int curans) {
  ans[v] = curans;
  for (Q q : g[v]) {
    if (q.t == 1 && !inv[q.i]) {
      int has = a[q.i][q.j];
      a[q.i][q.j] = 1;
      sum[q.i] += 1 - has;
      go(q.u, curans + 1 - has);
      sum[q.i] -= 1 - has;
      a[q.i][q.j] = has;
    }
    if (q.t == 1 && inv[q.i]) {
      int has = a[q.i][q.j];
      a[q.i][q.j] = 0;
      sum[q.i] += has;
      go(q.u, curans + has);
      sum[q.i] -= has;
      a[q.i][q.j] = has;
    }
    if (q.t == 2 && !inv[q.i]) {
      int has = a[q.i][q.j];
      a[q.i][q.j] = 0;
      sum[q.i] -= has;
      go(q.u, curans - has);
      sum[q.i] += has;
      a[q.i][q.j] = has;
    }
    if (q.t == 2 && inv[q.i]) {
      int has = a[q.i][q.j];
      a[q.i][q.j] = 1;
      sum[q.i] -= 1 - has;
      go(q.u, curans - 1 + has);
      sum[q.i] += 1 - has;
      a[q.i][q.j] = has;
    }
    if (q.t == 3) {
      curans -= sum[q.i];
      sum[q.i] = m - sum[q.i];
      curans += sum[q.i];
      inv[q.i] ^= true;
      go(q.u, curans);
      inv[q.i] ^= true;
      curans -= sum[q.i];
      sum[q.i] = m - sum[q.i];
      curans += sum[q.i];
    }
    if (q.t == 4) {
      go(q.u, curans);
    }
  }
}

int main() {
#if __APPLE__
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif

  int q;
  scanf("%d%d%d", &n, &m, &q);

  for (int id = 1; id <= q; id++) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int i, j;
      scanf("%d%d", &i, &j);
      --i, --j;
      g[id - 1].push_back(Q(t, id, i, j));
    }
    if (t == 2) {
      int i, j;
      scanf("%d%d", &i, &j);
      --i, --j;
      g[id - 1].push_back(Q(t, id, i, j));
    }
    if (t == 3) {
      int i;
      scanf("%d", &i);
      --i;
      g[id - 1].push_back(Q(t, id, i, -1));
    }
    if (t == 4) {
      int k;
      scanf("%d", &k);
      g[k].push_back(Q(t, id, -1, -1));
    }
  }
  
  go(0, 0);
  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]);
  }
}
