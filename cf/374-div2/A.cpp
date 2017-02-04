#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif
    
    int n;
    cin >> n;

    string s;
    cin >> s;

    int cnt = 0;
    vector<int> ans;
    for (int i = 0; i != n; ++i) {
        if (s[i] == 'B') {
            cnt++;
        } else if (cnt > 0) {
            ans.push_back(cnt);
            cnt = 0;
        }
    }
    if (cnt != 0) {
        ans.push_back(cnt);
    }

    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}
