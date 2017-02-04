#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  freopen("F.in", "r", stdin);
  freopen("F.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);

  while (t--) {
    int n, k;
    scanf("%d%d", &n, &k);

    int a[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", a + i);
    }

    for (int z = 0; z < n; z++)
    for (int i = 0; i < n; i++) {
      for (int j = 0; j + k < n; j++) {
        if (a[j] > a[j + k]) {
          swap(a[j], a[j + k]);
        }
      }
    }

    bool ok = true;
    for (int i = 1; i < n; i++) {
      if (a[i] < a[i - 1]) {
        puts("Unsafe");
        ok = false;
        break;
      }
    }
    
    if (ok) puts("Safe");
  }
}
