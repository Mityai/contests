#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#define ll long long
using namespace std;

vector<ll> t;

ll max_(ll a, ll b) {
    if (a >= b) {
        return a;
    }
    return b;
}

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
    return sum(v*2, l0, m, l, m) + sum(v*2+1, m+1, r0, m+1, r);
}

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    
    int n;
    cin >> n;
    char lastc = '+';
    ll lastres;
    set<ll> nums;
    t.resize(1200000);
    int kolvo = 1;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            int x;
            cin >> x;
            if (lastc == '+') {
                if (nums.count(x) == 0) {
                    add(1, 1, 300000, kolvo, x);
                    kolvo++;
                    nums.insert(x);
                }
            } else {
                ll x_ = (x + lastres) % 1000000000;
                if (nums.count(x_) == 0) {
                    add(1, 1, 300000, kolvo, x_);
                    kolvo++;
                    nums.insert(x_);
                }
            }
        } else {
            ll l, r;
            cin >> l >> r;
            lastres = sum(1, 1, 300000, l, r);
            cout << lastres << endl;
        }
        lastc = c;
    }
}