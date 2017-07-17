#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

int main() {
    ll n, k;
    scanf("%lld%lld", &n, &k);

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }

    sort(a.begin(), a.end());

    ll lb = -1, rb = 1e9;
    while (lb + 1 < rb) {
        ll mb = (lb + rb) / 2;
        ll cnt = 0;
        for (int i = 0, id = 0; i < n; ++i) {
            while (id < n && a[id] - a[i] <= mb) ++id;
            //int id = int(upper_bound(a.begin(), a.end(), a[i] + mb) - a.begin());
            cnt += id - i - 1;
        }
        if (cnt < k) {
            lb = mb;
        } else {
            rb = mb;
        }
    }
    printf("%lld\n", rb);
}
