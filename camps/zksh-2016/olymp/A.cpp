#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1234567890;

ll T(ll a, ll b, ll x, ll y) {
    ll tA = x * b + y;
    ll tB = y * a;
    ll t1 = abs(tA - tB);
    ll t2 = a * b - t1;
    return min(t1, t2);
}

int main() {
    ll a, b, x, y;
    scanf("%lld%lld%lld%lld", &a, &b, &x, &y);

    ll t = T(a, b, x, y);
    while (true) {
        y = y + 1;
        if (y == b) y = 0;
        if (y == 0) x = x + 1;
        if (x == a) x = 0;
        if (t == T(a, b, x, y)) {
            cout << x << ' ' << y << endl;
            return 0;
        }
    }
}
