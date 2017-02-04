#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5;
const int K = 19;

int SP[K][N][2];
int LOG[N + 1];

void calcLog() {
  for (int i = 2; i <= N; i++) {
    LOG[i] = LOG[i / 2] + 1;
  }
}

void build(int n, int *a, int *b) {
  for (int i = 0; i < n; i++) {
    SP[0][i][0] = a[i];
    SP[0][i][1] = b[i];
  }
  for (int k = 0; (1 << (k + 1)) <= n; k++) {
    for (int i = 0; i + (1 << (k + 1)) <= n; i++) {
      SP[k + 1][i][0] = max(SP[k][i][0], SP[k][i + (1 << k)][0]);
      SP[k + 1][i][1] = min(SP[k][i][1], SP[k][i + (1 << k)][1]);
    }
  }
}

int getMax(int l, int r) {
  int k = LOG[r - l + 1];
  return max(SP[k][l][0], SP[k][r - (1 << k) + 1][0]);
}

int getMin(int l, int r) {
  int k = LOG[r - l + 1];
  return min(SP[k][l][1], SP[k][r - (1 << k) + 1][1]);
}

int main() {
  int n;
  scanf("%d", &n);

  int a[n], b[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", b + i);
  }

  calcLog();
  build(n, a, b);

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    int rightbound = -1;
    {
      int lb = i - 1, rb = n;
      while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        int X = getMax(i, mb);
        int Y = getMin(i, mb);
        if (X > Y) rb = mb;
        else lb = mb;
      }
      rightbound = rb;
    }
    int leftbound = n + 1;
    {
      int lb = i - 1, rb = n;
      while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        int X = getMax(i, mb);
        int Y = getMin(i, mb);
        if (X < Y) lb = mb;
        else rb = mb;
      }
      leftbound = rb;
    }
    if (leftbound < rightbound) {
      ans += rightbound - leftbound;
    }
  }

  printf("%lld\n", ans);
}
