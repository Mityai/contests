#include <bits/stdc++.h>
#define get adslsk
#define down asjldfk
#define right dkajsdfl
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1123;

int get(int i, int j) {
  return i * N + j;
}

int n, m, q;
int down[N * N], right[N * N], val[N * N];

int go(int y, int x) {
  int cur = 0;
  for (int i = 0; i < x; i++) {
    cur = right[cur];
  }
  for (int i = 0; i < y; i++) {
    cur = down[cur];
  }
  return cur;
}

int main() {
#if __APPLE__
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif

  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &val[get(i, j)]);
    }
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      down[get(i, j)] = get(i + 1, j);
      right[get(i, j)] = get(i, j + 1);
    }
  }
  
  for (int i = 0; i < q; i++) {
    int a, b, c, d, h, w;
    scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &h, &w);

    int f1 = go(a, b - 1);
    int f2 = go(c, d - 1);
    int f3 = go(a - 1, b);
    int f4 = go(c - 1, d);
    int f5 = go(a, b + w - 1);
    int f6 = go(c, d + w - 1);
    int f7 = go(a + h - 1, b);
    int f8 = go(c + h - 1, d);

    int x = f1, y = f2;
    for (int j = 0; j < h; j++) {
      swap(right[x], right[y]);
      x = down[x];
      y = down[y];
    }

    x = f3, y = f4;
    for (int j = 0; j < w; j++) {
      swap(down[x], down[y]);
      x = right[x];
      y = right[y];
    }

    x = f5, y = f6;
    for (int j = 0; j < h; j++) {
      swap(right[x], right[y]);
      x = down[x];
      y = down[y];
    }

    x = f7, y = f8;
    for (int j = 0; j < w; j++) {
      swap(down[x], down[y]);
      x = right[x];
      y = right[y];
    }
  }

  for (int i = 1; i <= n; i++) {
    int cur = get(i, 0);
    for (int j = 1; j <= m; j++) {
      cur = right[cur];
      printf("%d ", val[cur]);
    }
    puts("");
  }
}
