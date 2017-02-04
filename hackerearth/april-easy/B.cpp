#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;

int nxt[N][26];

bool has(string &t) {
    int v = nxt[0][t[0] - 'a'];
    if (v == -1) return false;
    for (int i = 1; i < (int)t.length(); i++) {
        v = nxt[v + 1][t[i] - 'a'];
        if (v == -1) return false;
    }
    return true;
}

int main() {
    string s;
    cin >> s;

    int n = (int)s.length();
    memset(nxt, -1, sizeof nxt);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][s[i] - 'a'] = i;
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        string t;
        cin >> t;

        if (has(t)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
}
