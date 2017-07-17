#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

void imp() {
    cout << "IMPOSSIBLE\n";
}

void solve() {
    int l, s;
    cin >> l >> s;

    vector<pair<int, string>> q(s);
    for (int i = 0; i < s; ++i) {
        cin >> q[i].fi >> q[i].se;
        --q[i].fi;
    }

    string ans(l, '*');
    for (int i = 0; i < s; ++i) {
        int p = q[i].fi;
        string& suf = q[i].se;

        int len_ast = l - p - int(suf.size()) + 1;
        for (int j = p, k = 0; k < suf.size(); ++j, ++k) {
            if (suf[k] == '*') {
                j += len_ast - 1;
                continue;
            }
            if (ans[j] != '*' && ans[j] != suf[k]) {
                imp();
                return;
            }
            ans[j] = suf[k];
        }
    }
    for (char c : ans) {
        if (c == '*') {
            imp();
            return;
        }
    }
    cout << ans << '\n';
}

int main() {
#if __APPLE__
    freopen("H.in", "r", stdin);
    freopen("H.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    for (int test = 0; test < t; ++test) {
        solve();
    }
}
