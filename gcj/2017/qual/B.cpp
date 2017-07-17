#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool tidy(ll x) {
  ll prev = 9;
  while (x > 0) {
    if (prev < x % 10) {
      return false;
    }
    prev = x % 10;
    x /= 10;
  }
  return true;
}

ll stup(ll n) {
  for (ll x = n; x >= 1; --x) {
    if (tidy(x)) {
      return x;
    }
  }
}

ll solve(ll n) {
  string s = to_string(n);
  for (int i = 0; i + 1 < s.length(); ++i) {
    if (s[i] > s[i + 1]) {
      int last;
      for (int j = i; j >= 0; --j) {
        s[j] = char((s[j] - '0' + 9) % 10 + '0');
        last = j;
        if (s[j] != '9' && (j == 0 || s[j - 1] <= s[j])) {
          break;
        }
      }
      for (int j = last + 1; j < s.length(); ++j) {
        s[j] = '9';
      }
      break;
    }
  }
  while (*s.begin() == '0') s.erase(s.begin());
  return stoll(s);
}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int main() {
#if __APPLE__
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);

  for (int test = 1; test <= t; ++test) {
    ll n;
    scanf("%lld", &n);

    printf("Case #%d: %lld\n", test, solve(n));
  }
}
