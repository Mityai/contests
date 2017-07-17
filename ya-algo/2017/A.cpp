#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    string s, t;
    cin >> s >> t;

    vector<char> ch(26);
    for (char c : s) {
        ++ch[c - 'a'];
    }
    for (char c : t) {
        --ch[c - 'a'];
    }
    bool ok = true;
    for (int x : ch) {
        ok &= (x == 0);
    }

    if (!ok) {
        puts("-1");
        return 0;
    }

    int n = s.size();
    int l = 0, r = n - 1;
    int ans = 0;
    while (l < r) {
        while (l < n && s[l] == t[l]) ++l;
        while (r >= 0 && s[r] == t[r]) --r;
        if (r <= l) break;
        int f = r;
        while (s[f] != t[l]) --f;
        rotate(s.begin() + l, s.begin() + f, s.begin() + f + 1);
        ++ans;
    }
    cout << ans << endl;
}
