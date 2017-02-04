#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll a1, b1, a2, b2, L, R;
ll A, B, C;

ll gcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1, y = 0; return a;
  }
  ll x1, y1;
  ll ret = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return ret;
}

bool getsol(ll a, ll b, ll c, ll &x, ll &y) {
  ll g = gcd(abs(a), abs(b), x, y);
  if (c % g != 0) return false;
  x *= c / g;
  y *= c / g;
  if (a < 0) x = -x;
  if (b < 0) y = -y;
  return true;
}

ll lcm(ll a, ll b) {
  ll x, y;
  return a * b / gcd(a, b, x, y);
}

ll solve(ll n, ll k, ll l) {
  ll sa = b1 + k * a1;
  ll sb = b2 + l * a2;
  ll lc = lcm(a1, a2);
  ll ret = 0;
  ret += (b1 == b2 && b1 <= n);
  ret += (sa == sb && sa <= n);
  if (sa == b1 && sb == b2 && sa == sb && sa <= n) ret--;
  ll lb = 0, rb = 5e9;
  while (lb + 1 < rb) {
    ll mb = (lb + rb) / 2;
    if (sa + lc * mb <= n) lb = mb;
    else rb = mb;
  }
  return ret + lb;
}

int main() {
#if __APPLE__
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  while (cin >> a1 >> b1 >> a2 >> b2 >> L >> R) {
    ll x, y;
    ll g = gcd(a1, a2, x, y);
    A = a1, B = -a2, C = b2 - b1;
    if (!getsol(A, B, C, x, y)) {
      cout << 0 << endl;
      continue;
    }
    while (x + B / g >= 0 && y - A / g >= 0) {
      x += B / g;
      y -= A / g;
    }
    while (x < 0 || y < 0) {
      x -= B / g;
      y += A / g;
    }
    ll f1 = solve(R, x, y);
    ll f2 = solve(L - 1, x, y);
    cout << f1 - f2 << endl;
  }
}
