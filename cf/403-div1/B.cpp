#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

struct Name {
    string a, b;
    int i;
};

void no() {
    cout << "NO\n";
}

void solve(int n) {
    vector<Name> same;
    vector<Name> other;
    map<string, int> cnt;
    for (int i = 0; i < n; ++i) {
        string s, t;
        cin >> s >> t;
        string a = s.substr(0, 3);
        string b = s.substr(0, 2) + t.substr(0, 1);
        if (a == b) {
            same.push_back({a, b, i});
        } else {
            ++cnt[a];
            other.push_back({a, b, i});
        }
    }

    vector<Name> several;
    vector<Name> ones;
    for (int i = 0; i < other.size(); ++i) {
        if (cnt[other[i].a] > 1) {
            several.push_back(other[i]);
        } else {
            ones.push_back(other[i]);
        }
    }

    vector<string> ans(n);
    set<string> was;
    for (auto& p : same) {
        if (was.find(p.a) != was.end()) {
            no();
            return;
        } else {
            ans[p.i] = p.a;
            was.insert(p.a);
        }
    }

    for (auto& p : several) {
        if (was.find(p.b) != was.end()) {
            no();
            return;
        } else {
            ans[p.i] = p.b;
            was.insert(p.b);
        }
    }

    for (auto& p : ones) {
        if (was.find(p.b) == was.end()) {
            ans[p.i] = p.b;
            was.insert(p.b);
        } else if (was.find(p.a) == was.end()) {
            ans[p.i] = p.a;
            was.insert(p.a);
        } else {
            no();
            return;
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
    }
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        solve(n);
    }
}
