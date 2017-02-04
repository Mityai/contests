#include <bits/stdc++.h>
#define next hkjsadf
using namespace std;

const int N = 1e6;
const int C = 26;
const int K = 1e3;

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
    int n;
    scanf("%d", &n);
    
    string s;
    cin >> s;

    s = "#" + s;

    int m;
    scanf("%d", &m);

    memset(next, -1, sizeof next);
    memset(leaf, -1, sizeof leaf);

    vector<string> t(m);
    for (int i = 0; i < m; i++) {
        cin >> t[i];
        string tmp = "";
        for (char c : t[i]) {
            tmp += tolower(c);
        }
        add(tmp, i);
    }

    bool dp[n + 1];
    int p[n + 1];
    memset(dp, 0, sizeof dp);
    memset(p, -1, sizeof p);

    dp[0] = true;
    for (int i = 1; i <= n; i++) {
        int v = 0;
        for (int j = i; j >= max(1, i - K); j--) {
            int x = s[j] - 'a';
            if (next[v][x] == -1) break;
            v = next[v][x];
            if (leaf[v] != -1) {
                if (dp[j - 1]) {
                    dp[i] = true;
                    p[i] = leaf[v];
                    break;
                }
            }
        }
    }

    vector<string> ans;
    for (int i = n; i >= 1; i -= t[p[i]].length()) {
        ans.push_back(t[p[i]]);
    }

    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        printf("%s ", ans[i].c_str());
    }
    puts("");
}
