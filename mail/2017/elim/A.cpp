#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e15;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        ll a, b;
        scanf("%lld%lld", &a, &b);

        ll g = gcd(a, b);
        a /= g;
        b /= g;

        map<int, int> pa;
        {
            ll x = a;
            for (ll p = 2; p * p <= x; ++p) {
                while (x % p == 0) {
                    ++pa[p];
                    x /= p;
                }
            }
            if (x != 1) {
                ++pa[x];
            }
        }
        {
            ll x = b;
            for (ll p = 2; p * p <= x; ++p) {
                while (x % p == 0) {
                    ++pa[p];
                    x /= p;
                }
            }
            if (x != 1) {
                ++pa[x];
            }
        }
        vector<ll> ps;
        for (auto& p : pa) {
            p.second &= 1;
            if (p.second) {
                ps.push_back(p.first);
            }
        }

        ll ans1 = INF, ans2 = INF;
        for (int mask = 0; mask < (1 << ps.size()); ++mask) {
            ll cura = 1, curb = 1;
            for (int i = 0; i < ps.size(); ++i) {
                if ((mask >> i) & 1) {
                    cura *= ps[i];
                } else {
                    curb *= ps[i];
                }
            }
            if (ans1 + ans2 > cura + curb) {
                ans1 = cura;
                ans2 = curb;
            }
        }

        printf("%lld %lld\n", ans1, ans2);
    }
}
