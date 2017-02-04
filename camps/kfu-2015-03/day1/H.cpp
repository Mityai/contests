#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    freopen("abc.in", "r", stdin);
    freopen("abc.out", "w", stdout);

    string s;
    cin >> s;

    int n = (int)s.length();
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = (s[i] == 'a') + (i > 0 ? a[i - 1] : 0);
    }

    ll ans = 0;
    for (int i = n - 1, c = 0; i >= 0; i--) {
        if (s[i] == 'c') c++;
        if (s[i] == 'b') ans += a[i] * 1LL * c;
    }

    cout << ans << endl;
}
