#include <bits/stdc++.h>
#define fi first
#define se secdond
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    ll n, k;
    scanf("%lld%lld", &n, &k);

    ll lb = 0, rb = 1;
    while (rb + rb * k <= n / 2) rb *= 2;
    while (lb + 1 < rb) {
        ll mb = (lb + rb) / 2;
        ll cnt = mb + mb * k;
        if (cnt > n / 2) {
            rb = mb;
        } else {
            lb = mb;
        }
    }

    printf("%lld %lld %lld\n", lb, lb * k, n - lb - lb * k);
}
