#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios_base::sync_with_stdio(false);

    ull n, k, m, d;
    cin >> n >> k >> m >> d;

    ull ans = 0;
    for (ull t = 1; t <= d; ++t) {
        ull lb = 1, rb = min(m, n) + 1;
        while (lb + 1 < rb) {
            ull mb = (lb + rb) / 2;
            ull cnt = (n / mb + k - 1) / k;
            if (cnt >= t) {
                lb = mb;
            } else {
                rb = mb;
            }
        }
        if ((n / lb + k - 1) / k == t) {
            ans = max(ans, lb * t);
        }
    }

    cout << ans << endl;
}
