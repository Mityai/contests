#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool isprime(ll x) {
    if (x == 2) return true;
    if (x == 1 || x % 2 == 0) return false;
    for (ll p = 3; p * p <= x; p += 2) {
        if (x % p == 0) return false;
    }
    return true;
}

string tostr(ll x) {
    string ret = "";
    while (x > 0) {
        ret += char(x % 10 + '0');
        x /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    srand(time(NULL));

    int n;
    scanf("%d", &n);

    ll x = 0;
    if (n > 0) {
        scanf("%lld", &x);
    }

    int len = 12 - n;
    ll ten = 1;
    for (int i = 0; i < len; i++) {
        ten *= 10;
    }

    while (true) {
        ll y = rand() % ten;
        ll a = x * ten + y;
        if (isprime(a)) {
            string ans = tostr(a);
            while (ans.size() < 12) ans.insert(ans.begin(), '0');
            cout << ans << endl;
            return 0;
        }
    }
}
