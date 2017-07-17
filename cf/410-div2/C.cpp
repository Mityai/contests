#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

ll gcd_(ll a, ll b) {
    return b ? gcd_(b, a % b) : a;
}

ll gcd(ll a, ll b) {
    return gcd_(llabs(a), llabs(b));
}

void yes(int x) {
    printf("YES\n%d\n", x);
    exit(0);
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<ll> a(n);
    ll g = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
        g = gcd(g, a[i]);
    }

    if (g > 1) {
        yes(0);
    }

    int ans = 0;
    for (int i = 0; i + 1 < n; ++i) {
        if (a[i] % 2 == 1 && a[i + 1] % 2 == 1) {
            ll t1 = a[i];
            ll t2 = a[i + 1];
            a[i] = t1 - t2;
            a[i + 1] = t1 + t2;
            ++ans;
        }
    }
    for (int i = 0; i + 1 < n; ++i) {
        while (gcd(a[i], a[i + 1]) % 2 != 0) {
            ll t1 = a[i];
            ll t2 = a[i + 1];
            a[i] = t1 - t2;
            a[i + 1] = t1 + t2;
            ++ans;
        }
    }

    yes(ans);
}
