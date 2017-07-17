#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <map>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef long double ld;

const long double inf = 1e18 + 7;

const long double eps = 1e-18;



ll gcd(ll a, ll b) {
    while (a && b)
        a %= b, swap(a, b);
    return a + b;
}

ll emaxxgcd(ll a, ll b, ll & x, ll & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	ll xx, yy;
	ll d = emaxxgcd (b%a, a, xx, yy);
	x = yy - (b / a) * xx;
	y = xx;
	return d;
}

set<ll> nums;
map<ll, vector<ll> > gg;

vector<ll> parent, dp;

#define _DEBUG
int main() {
ios_base::sync_with_stdio(0);
#ifdef _DEBUG
    freopen("D.in", "r", stdin);
    freopen("D.out" "w", stdout);
#endif

    ll n, m;

    cin >> n >> m;
    if (n == 0 && m == 0){
        cout << 0;
        return 0;
    }
    parent.resize(m, -1);
    dp.resize(m);

    for (ll i = 0; i < m; ++i)
        nums.insert(i);
    for (ll i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        nums.erase(x);
    }

    for (auto x : nums)
       gg[gcd(x, m)].push_back(x);


    vector<ll> canuse;
    for (auto x : gg)
        if (x.first)
            canuse.push_back(x.first);

    for (ll i = canuse.size() - 1; i >= 0; --i) {
        for (ll j = i + 1; j < canuse.size(); ++j)
            if (dp[j] > dp[i] && !(canuse[j] % canuse[i]))
                dp[i] = dp[j], parent[i] = j;
        dp[i] += gg[canuse[i]].size();
    }
     
    ll maxx = dp[0];
    ll v = 0;
    for (ll i = 0; i < dp.size(); ++i)
        if (dp[i] > maxx)
            maxx = dp[i], v = i;
    
    cout << maxx << endl;
    ll past = 1;
    while (v != -1) {
        for (auto x : gg[canuse[v]]) {
            ll a, b;
            ll y = emaxxgcd(past, m, a, b);
            ll ans = (a * x / y) % m;
            if (ans <= 0)
                ans = (ans % m + m) % m;
            cout << ans << ' ';
            past = x;
        }
        v = parent[v];
    }
    return 0;
}
