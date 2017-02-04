#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }

    map<int, int> cnt;
    int odd[n + 1], even[n + 1];
    memset(odd, 0, sizeof odd);
    memset(even, 0, sizeof even);

    for (int i = 1; i <= n; i++) {
      odd[i] = odd[i - 1], even[i] = even[i - 1];
      cnt[a[i]]++;
      if (cnt[a[i]] & 1) {
        if (cnt[a[i]] > 1) {
          even[i] ^= a[i];
        }
        odd[i] ^= a[i];
      } else {
        even[i] ^= a[i];
        odd[i] ^= a[i];
      }
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
      int l, r;
      scanf("%d%d", &l, &r);
      --l;

      int ans = (even[r] ^ even[l] ^ odd[r] ^ odd[l]);
      printf("%d\n", ans);
    }
  }
}
