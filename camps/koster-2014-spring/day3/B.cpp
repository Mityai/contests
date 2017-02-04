#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <climits>
#define ll long long
using namespace std;
  
vector<ll> mn, mx;
 
ll max_(ll a, ll b) {
    if (a >= b) {
        return a;
    }
    return b;
}
 
ll min_(ll a, ll b) {
    if (a < b) {
        return a;
    }
    return b;
}
  
void add_mx(ll v, ll l0, ll r0, ll pos, ll val) {
    if (l0 == r0) {
        mx[v] = val;
    } else {
        ll m = (l0 + r0) / 2;
        if (pos <= m) {
            add_mx(v*2, l0, m, pos, val);
        } else {
            add_mx(v*2+1, m+1, r0, pos, val);
        }
        mx[v] = max_(mx[v*2], mx[v*2+1]);
    }
}
  
ll max_in(ll v, ll l0, ll r0, ll l, ll r) {
    if (l > r) {
        return LLONG_MIN;
    }
    if (l == l0 && r == r0) {
        return mx[v];
    }
    ll m = (l0 + r0) / 2;
    return max_(max_in(v*2, l0, m, l, min(r, m)), max_in(v*2+1, m+1, r0, max(l, m+1), r));
}
 
void add_mn(ll v, ll l0, ll r0, ll pos, ll val) {
    if (l0 == r0) {
        mn[v] = val;
    } else {
        ll m = (l0 + r0) / 2;
        if (pos <= m) {
            add_mn(v*2, l0, m, pos, val);
        } else {
            add_mn(v*2+1, m+1, r0, pos, val);
        }
        mn[v] = min_(mn[v*2], mn[v*2+1]);
    }
}
  
ll min_in(ll v, ll l0, ll r0, ll l, ll r) {
    if (l > r) {
        return LLONG_MAX;
    }
    if (l == l0 && r == r0) {
        return mn[v];
    }
    ll m = (l0 + r0) / 2;
    return min_(min_in(v*2, l0, m, l, min(r, m)), min_in(v*2+1, m+1, r0, max(l, m+1), r));
}
 
ll f(ll a) {
    return (a*a) % 12345 + (a*a*a) % 23456;
}
  
int main() {
    freopen("rvq.in", "r", stdin);
    freopen("rvq.out", "w", stdout);
      
    ll k;
    cin >> k;
    mx.resize(400001, LLONG_MIN);
    mn.resize(400001, LLONG_MAX);
    for (ll i = 0; i < 100000; i++) {
        ll val = f(i+1);
        add_mx(1, 1, 100000, i+1, val);
        add_mn(1, 1, 100000, i+1, val);
    }
    for (ll ii = 0; ii < k; ii++) {
        ll x, y;
        cin >> x >> y;
        if (x < 0) { //a[abs(x)] = y
            add_mx(1, 1, 100000, abs(x), y);
            add_mn(1, 1, 100000, abs(x), y);
        } else { //max(a[x..y])-min(a[x..y])
            cout << max_in(1, 1, 100000, x, y) - min_in(1, 1, 100000, x, y) << endl; 
        }
    }
}