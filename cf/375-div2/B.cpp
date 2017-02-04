#include <bits/stdc++.h>
#define fi first
#define se second
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

    int bal = 0;
    int cnt = 0, maxlen = 0;
    int len = 0;
    for (int i = 0; i != n; ++i) {
        if (isalpha(s[i])) {
            len++;
        } else {
            if (len > 0) {
                if (bal == 0) {
                    maxlen = max(maxlen, len);
                } else {
                    ++cnt;
                }
                len = 0;
            }
        }
        if (s[i] == '(') ++bal;
        if (s[i] == ')') --bal;
    }
    if (len != 0) {
        maxlen = max(maxlen, len);
    }
    cout << maxlen << ' ' << cnt << '\n';
}
