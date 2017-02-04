#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

int main() {
  ll n, a, b, p, q;
  while (cin >> n >> a >> b >> p >> q) {
    ll A = n / a;
    ll B = n / b;
    ll C = n / lcm(a, b);
    A -= C;
    B -= C;
    ll ans = A * p + B * q + C * max(p, q);
    cout << ans << endl;
  }
}
