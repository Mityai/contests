#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#define ll long long
using namespace std;
 
vector<ll> t;
 
void add(ll v, ll l0, ll r0, ll pos, ll val) {
    if (l0 == r0) {
        t[v] = val;
    } else {
        ll m = (l0 + r0) / 2;
        if (pos <= m) {
            add(v*2, l0, m, pos, val);
        } else {
            add(v*2+1, m+1, r0, pos, val);
        }
        t[v] = t[v*2] + t[v*2+1];
    }
}
 
ll sum(ll v, ll l0, ll r0, ll l, ll r) {
    if (l > r) {
        return 0;
    }
    if (l == l0 && r == r0) {
        return t[v];
    }
    ll m = (l0 + r0) / 2;
    return sum(v*2, l0, m, l, min(r, m)) + sum(v*2+1, m+1, r0, max(l, m+1), r);
}
 
int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
     
    ll n, k;
    cin >> n >> k;
    t.resize(4*n, 0);
    for (ll ii = 0; ii < k; ii++) {
        string q;
        cin >> q;
        if (q == "A") {
            ll i, x;
            cin >> i >> x;
            add(1, 1, n, i, x);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << sum(1, 1, n, l, r) << endl;
        }
    }
}