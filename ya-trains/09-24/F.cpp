#include <bits/stdc++.h> 
#define fi first
#define se second
using namespace std;

using ll = long long;

ll pw(int k) {
    ll res = 1;
    while (k--) res *= 10ll;
    return res;
}

vector<ll> find(ll n) {
    vector<ll> res;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            res.push_back(n / i);    
        }
    }
    return res;
}

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    int num = 1;
    while (n --> 0) {
        string s;
        cin >> s;
        cout << "Case " << num++ << ": ";
        map<char, ll> sum;

        for (int i = 0; i < s.size(); i++) {
            sum[s[i]] += pw(s.size() - i - 1);
        }

        ll g = 0;

        for (auto u: sum) { 
            g = gcd(g, u.second);
        }

        vector<ll> res = find(g);

        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        //maxim pidor
        for (ll x: res) cout << x << " ";
        cout << '\n';
    }
}   
