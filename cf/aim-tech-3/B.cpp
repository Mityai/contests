#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

void no() {
  puts("Impossible");
  exit(0);
}

ll a[2][2];

void calc(ll cnt0, ll cnt1) {
  ll cnt01 = cnt0 * cnt1;

  if (cnt0 * (cnt0 - 1) / 2 == a[0][0] && cnt1 * (cnt1 - 1) / 2 == a[1][1] && a[0][1] + a[1][0] == cnt01) {
    ll cnt10 = 0;
    ll firstone = 0;
    if (cnt0 != 0) {
      while (cnt10 + cnt0 <= a[1][0]) {
        cnt10 += cnt0;
        firstone++;
      }
    } else if (cnt10 + cnt0 != a[1][0]) {
      return;
    }
    ll left = a[1][0] - cnt10;
    for (int i = 0; i < firstone; i++) {
      putchar('1');
    }
    for (int i = 0; i < cnt0 - left; i++) {
      putchar('0');
    }
    if (firstone != cnt1) {
      putchar('1');
    }
    for (int i = 0; i < left; i++) {
      putchar('0');
    }
    for (int i = 0; i < cnt1 - firstone - 1; i++) {
      putchar('1');
    }
    exit(0);
  }
}

int main() {
#if __APPLE__
#endif

  cin >> a[0][0] >> a[0][1] >> a[1][0] >> a[1][1];
  if (a[0][0] + a[0][1] + a[1][0] + a[1][1] == 0) {
    putchar('1');
    return 0;
  }

  ll cnt0, cnt1;
  for (cnt0 = 0; cnt0 * (cnt0 - 1) / 2 <= a[0][0]; cnt0++);
  while (cnt0 * (cnt0 - 1) / 2 > a[0][0]) cnt0--;
  for (cnt1 = 0; cnt1 * (cnt1 - 1) / 2 <= a[1][1]; cnt1++);
  while (cnt1 * (cnt1 - 1) / 2 > a[1][1]) cnt1--;

  for (int i = -3; i <= 0; i++) {
    for (int j = -3; j <= 0; j++) {
      calc(max(0LL, cnt0 + i), max(0LL, cnt1 + j));
    }
  }
  no();
}
