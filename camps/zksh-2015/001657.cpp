#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair<pair<ll, ll>, int> PLL;

bool cmpa(PLL a, PLL b) {
    return a.fi.fi < b.fi.fi || (a.fi.fi == b.fi.fi && a.fi.se < b.fi.se);
}

bool cmpb(PLL a, PLL b) {
    return a.fi.fi + a.fi.se > b.fi.fi + b.fi.se;
}

auto cmp = [](PLL a, PLL b) {
    return a.fi.se < b.fi.se;
};

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
#else
    freopen("authority.in", "r", stdin);
    freopen("authority.out", "w", stdout);
#endif

    int n;
    ll c;

    cin >> n >> c;

    vector<PLL> a, b;
    for (int i = 0; i < n; i++) {
        ll ca, cb;
        cin >> ca >> cb;

        if (cb >= 0) {
            a.push_back({{ca, cb}, i + 1});
        } else {
            b.push_back({{ca, cb}, i + 1});
        }
    }

    sort(a.begin(), a.end(), cmpa);
    sort(b.begin(), b.end(), cmpb);

    // for (int i = 0; i < b.size(); i++) {
    //  cout << b[i].fi.fi << ' ' << b[i].fi.se << endl;
    // }

    vector<int> ans;
    for (int i = 0; i < (int)a.size() && a[i].fi.fi <= c; i++) {
        c += a[i].fi.se;
        ans.push_back(a[i].se);
    }

    vector<char> us(n + 1, false);
    multiset<PLL, decltype(cmp)> q(cmp);
    vector<int> ans2;
    for (auto t: b) {
        if (t.fi.fi <= c) {
            c += t.fi.se;
            q.insert(t);
            us[t.se] = true;
            ans2.push_back(t.se);
        } else {
			if (!q.empty()) {
				ll x = q.begin()->fi.se;
				if (t.fi.fi <= c - x && t.fi.se > x) {
					c -= x;
					us[q.begin()->se] = false;
					q.erase(q.begin());
					c += t.fi.se;
					us[t.se] = true;
					ans2.push_back(t.se);
					q.insert(t);
				}
			}
        }
    }

    for (auto x: ans2) {
        if (us[x] == true) {
            ans.push_back(x);
        }                              
    }

    printf("%d\n", (int)ans.size());
    for (auto x: ans) {
        printf("%d ", x);
    }
}
