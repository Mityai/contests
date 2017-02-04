#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n;
    int k;
    cin >> n >> k;

    vector<ll> all;
    all.reserve(1e5);
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            all.push_back(i);
            if (i * i != n) {
                all.push_back(n / i);
            }
        }
    }

    sort(all.begin(), all.end());

    if (k - 1 >= all.size()) {
        cout << -1 << endl;
    } else {
        cout << all[k - 1] << endl;
    }
}
