#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = LLONG_MAX;
const int N = 1e7 + 1;

ll ans[N];

int main() {
#if __APPLE__
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif

  ll n, x, y;
  cin >> n >> x >> y;

  for (int i = 0; i <= n; i++) {
    ans[i] = INF;
  }

  ans[0] = 0;
  ans[1] = x;
  for (ll i = 1; i <= n; i++) {
    if (i * 2 <= n) {
      ans[i * 2] = min(ans[i * 2], ans[i] + y);
    } else {
      ans[n] = min(ans[n], ans[i] + y + x * (i * 2 - n));
    }

    if (i * 2 - 1 <= n) {
      ans[i * 2 - 1] = min(ans[i * 2 - 1], ans[i] + y + x);
    }

    if (i + 1 <= n) {
      ans[i + 1] = min(ans[i + 1], ans[i] + x);
    }
    ans[n] = min(ans[n], ans[i] + x * (n - i));
  }

  cout << ans[n] << endl;
}
