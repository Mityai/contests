#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5;

int n;
int p[N], used[N], a[N];
int root = -1;

void go(int v) {
  used[v] = 1;

  if (p[v] == v) {
    if (root != v) {
      if (root == -1) root = v;
      p[v] = root;
    }
  } else if (used[p[v]] == 1) {
    if (root == -1) {
      root = v;
    }
    p[v] = root;
  } else if (used[p[v]] == 0) {
    go(p[v]);
  }

  used[v] = 2;
}

int main() {
#if __APPLE__
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif

  scanf("%d", &n);
  
  for (int i = 0; i < n; i++) {
    scanf("%d", p + i);
    --p[i];
    a[i] = p[i];
    if (i == p[i]) {
      root = i;
    }
  }

  for (int i = 0; i < n; i++) {
    if (used[i] == 0) {
      go(i);
    }
  }

  pair<int, int> F;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] != p[i]) {
      ans++;
    }
  }

  printf("%d\n", ans);
  for (int i = 0; i < n; i++) {
    printf("%d ", p[i] + 1);
  }
  puts("");
}
