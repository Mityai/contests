#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

// ads

string s, t;
int ans;

void go(string s) {
    if (s.length() == t.length()) {
        if (s == t) ans++;
        return;
    }

    for (int i = 0; i < (int)s.length(); i++) {
        if (s.length() + i + 1 > t.length()) break;
        string q = s.substr(0, i + 1);
        reverse(q.begin(), q.end());
        go(q + s);
    }

    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s.length() + s.length() - i > t.length()) break;
        string q = s.substr(i);
        reverse(q.begin(), q.end());
        go(s + q);
    }
}

int main() {
    cin >> s >> t;

    go(s);

    cout << ans << endl;
}
