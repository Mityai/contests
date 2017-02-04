#include <bits/stdc++.h>
#define next hisaskljdf
using namespace std;

const int N = 2e3 * 20;
const int C = 26;

int next[N][C], leaf[N];
int tc = 0;

void add(string &s, int id) {
    int v = 0;
    for (char c : s) {
        int x = c - 'a';
        if (next[v][x] == -1) next[v][x] = ++tc;
        v = next[v][x];
    }
    leaf[v] = id;
}

int main() {
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);

    memset(next, -1, sizeof next);
    memset(leaf, -1, sizeof leaf);

    string s;
    cin >> s;

    int n;
    scanf("%d", &n);

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        add(a[i], i);
    }

    int m = (int)s.length();
    s = "#" + s;

    int dp[m + 1], p[m + 1];
    memset(dp, 0, sizeof dp);

    dp[0] = true;
    for (int i = 1; i <= m; i++) {
        if (dp[i - 1]) {
            int v = 0;
            for (int j = i; j <= m; j++) {
                int x = s[j] - 'a';
                v = next[v][x];
                if (v == -1) break;
                if (leaf[v] != -1) {
                    dp[j] = true;
                    p[j] = leaf[v];
                }
            }
        }
    }

    vector<string> ans;
    for (int i = m; i != 0; i -= a[p[i]].length()) {
        ans.push_back(a[p[i]]);
    }

    reverse(ans.begin(), ans.end());

    for (string s : ans) {
        cout << s << ' ';
    }
    cout << endl;
}
