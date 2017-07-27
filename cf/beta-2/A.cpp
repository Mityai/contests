#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    map<string, int> cnt;
    vector<pair<string, int>> q(n);
    for (int i = 0; i < n; ++i) {
        cin >> q[i].first >> q[i].second;
        cnt[q[i].first] += q[i].second;
    }
    int mx = 0; for (auto& v : cnt) mx = max(mx, v.second);
    map<string, int> rep;

    for (int i = 0;; ++i) {
        rep[q[i].first] += q[i].second;
        if (rep[q[i].first] >= mx && cnt[q[i].first] == mx) {
            return cout << q[i].first << endl, 0;
        }
    }
}
