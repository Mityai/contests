#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1000 + 1;

char c[N];
string a[N];
bool good[N + 1][N + 1];

inline string next() {
  scanf(" %s", c);
  return string(c);
}

ll go(int i, int j, int n, int m, ll curans) {
  if (i == n && j == m) return curans;
  ll curbit = (1LL << (n + m - (i + j) - 1));
  if (j + 1 <= m && good[i][j + 1]) {
    ll ret = go(i, j + 1, n, m, curans);
    if (ret != -1) return ret;
  }
  if (i + 1 <= n && good[i + 1][j]) {
    ll ret = go(i + 1, j, n, m, curans + curbit);
    if (ret != -1) return ret;
  }
  return -1;
}

int main() {
#if __APPLE__
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif

  int n, k;
  scanf("%d%d", &n, &k);

  for (int i = 0; i < n; i++) {
    a[i] = next();
  }

  int anslen = k + 1;
  ll path = LLONG_MAX;
  for (int dx = 0; dx <= k; dx++) {
    for (int dy = 0; dx + dy <= k; dy++) {
      if (a[dx][dy] != '.') continue;
      if (dx + dy > anslen) continue;

      memset(good, 1, sizeof good);
      for (int i = 0; i <= dx; i++) {
        for (int j = 0; j <= dy; j++) {
          for (int f = 0; i + dx * f < n && j + dy * f < n; f++) {
            if (a[i + dx * f][j + dy * f] != '.') {
              good[i][j] = false;
              break;
            }
          }
        }
      }

      /*
      printf("for dx = %d and dy = %d\n", dx, dy);
      for (int i = 0; i <= dx; i++) {
        for (int j = 0; j <= dy; j++) {
          printf("%d", (int)good[i][j]);
        }
        puts("");
      }*/

      ll curans = go(0, 0, dx, dy, 0);
      if (curans != -1 && curans < path) path = curans, anslen = dx + dy;
    }
  }

  //printf("%d\n", anslen);
  for (int i = anslen - 1; i >= 0; i--) {
    printf("%lld", (path >> i) & 1LL);
  }
}
