#include <bits/stdc++.h>
#define fi first
#define se secodn
using namespace std;

using ll = long long;

int main() {
    string s;
    getline(cin, s);

    ll ans = 0;
    ll price = 0;
    ll cnt = 0;
    for (ll i = 0; i < (ll)s.length(); i++) {
        if (isalpha(s[i])) {
            if (price != 0) {
                ll k = 1;
                if (cnt != 2) {
                    k = 100;
                }
                ans += price * k;
            }
            cnt = 0;
            price = 0;
        } else {
            if (s[i] != '.') {
                price = price * 10 + s[i] - '0';
                cnt++;
            } else {
                cnt = 0;
            }
        }
    }
    if (price != 0) {
        ll k = 1;
        if (cnt != 2) {
            k = 100;
        }
        ans += price * k;
    }

    vector<ll> x;
    while (ans > 0) {
        x.push_back(ans % 10);
        ans /= 10;
    }
    string ret = "";
    for (ll y : x) {
        ret += char(y + '0');
    }
    while (ret.size() < 3) ret += "0";
    ret.insert(ret.begin() + 2, '.');
    for (ll i = ret.size() - 1; i >= 4; i--) {
        if ((i - 3) % 3 == 0) {
            ret.insert(ret.begin() + i, '.');
        }
    }
    if (ret[0] == '0' && ret[1] == '0') {
        ret.erase(ret.begin());
        ret.erase(ret.begin());
        ret.erase(ret.begin());
    }
    reverse(ret.begin(), ret.end());
    cout << ret << '\n';
}
