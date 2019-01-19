#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int highest(ll x) {
    int ret = 0;
    while (x > 0) {
        x >>= 1;
        ++ret;
    }
    return ret - 1;
}

void no() {
    puts("No");
    exit(0);
}

int main() {
    int n;
    scanf("%d", &n);

    map<int, vector<ll>> mp;
    for (int i = 0; i < n; ++i) {
        ll x;
        scanf("%lld", &x);
        mp[highest(x)].push_back(x);
    }

    vector<ll> ans;
    for (int bit = 59; bit >= 0; --bit) {
        vector<ll> newans;
        size_t q = 0;
        for (size_t j = 0; j < mp[bit].size(); ++j) {
            if (j != 0) {
                for (; q <= ans.size(); ++q) {
                    if (q == ans.size()) no();
                    newans.push_back(ans[q]);
                    if ((ans[q] >> bit) & 1) {
                        ++q;
                        break;
                    }
                }
            }
            newans.push_back(mp[bit][j]);
        }
        for (; q < ans.size(); newans.push_back(ans[q]), ++q);
        ans.swap(newans);
    }

    puts("Yes");
    for (ll x : ans) {
        printf("%lld ", x);
    }
    putchar('\n');
}
