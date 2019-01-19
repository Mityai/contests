#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll X = 1e9;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> a(n), b(m);
    int sum_a = 0, sum_b = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        sum_a += a[i];
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
        sum_b += b[i];
    }

    ll mx = *max_element(a.begin(), a.end());

    ll ans = sum_a * X + sum_b;

    int first_pos = -1, last_pos = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == mx) {
            if (first_pos == -1) {
                first_pos = i;
            }
            last_pos = i;
        }
    }

    ans += (m - 1) * mx * X;
    if (first_pos == last_pos) {
        ans += b[0] * first_pos + b[m - 1] * (n - last_pos - 1);
    } else {
        int mx_b = *max_element(b.begin(), b.end());
        ans += b[0] * first_pos + mx_b * (last_pos - first_pos) + b[m - 1] * (n - last_pos - 1);
    }

    printf("%lld\n", ans);
}
