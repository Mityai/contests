#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
#endif

    int k2, k3, k5, k6;
    cin >> k2 >> k3 >> k5 >> k6;

    ll ans = min({k2, k5, k6});
    k2 -= ans;
    ans *= 256;
    ans += 32 * min(k2, k3);
    cout << ans << endl;
}
