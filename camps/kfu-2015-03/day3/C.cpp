#include <bits/stdc++.h>
#define count asdsdjf
using namespace std;

vector<int> g[26];
bool used[26];
int count[26];

int cnt, mx;

void go(int v) {
    cnt += count[v];
    mx = max(mx, count[v]);
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            go(u);
        }
    }
}

int main() {
    freopen("tattarrattat.in", "r", stdin);
    freopen("tattarrattat.out", "w", stdout);

    string s;
    cin >> s;

    int n = (int)s.length();

    for (int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        count[x]++;
    }

    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1]) {
            int x = s[i] - 'a';
            int y = s[n - i - 1] - 'a';
            g[x].push_back(y);
            g[y].push_back(x);
        }
    }

    int ans = 0;
    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            cnt = 0, mx = 0;
            go(i);
            ans += cnt - mx;
        }
    }

    cout << ans << endl;
}
