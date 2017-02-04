#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
    ll k, r;
    cin >> k >> r;

    ll cur = k;
    int ans = 1;
    while (cur % 10 != 0 && cur % 10 != r) {
        cur += k;
        ++ans;
    }
    cout << ans << '\n';
}
