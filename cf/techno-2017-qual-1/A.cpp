#include <bits/stdc++.h>
#define fi first
#define se secodn
using namespace std;

using ll = long long;

int main() {
    int a, b;
    cin >> a >> b;

    queue<ll> q;
    q.push(a);

    map<ll, ll> p;

    while (!q.empty()) {
        ll v = q.front();
        q.pop();

        if (v == b) break;

        if (v * 10 + 1 <= b && p.find(v * 10 + 1) == p.end()) {
            q.push(v * 10 + 1);
            p[v * 10 + 1] = v;
        }
        if (v * 2 <= b && p.find(v * 2) == p.end()) {
            q.push(v * 2);
            p[v * 2] = v;
        }
    }

    if (p.find(b) == p.end()) {
        cout << "NO\n";
    } else {
        vector<int> ans;
        for (int v = b; v != a; v = p[v]) {
            ans.push_back(v);
        }
        ans.push_back(a);

        reverse(ans.begin(), ans.end());
        cout << "YES\n";
        cout << ans.size() << '\n';
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}
