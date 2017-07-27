#include <bits/stdc++.h>
using namespace std;

vector<int> get_pi(const string& s) {
    int n = s.length();
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = p[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        p[i] = j;
    }
    return p;
}

const int N = 8000;
vector<int> p[N];

int get_period(int suf, int len) {
    int p_last = p[suf][len - 1];
    int t = len - p_last;
    if (len % t != 0) {
        t = len;
    }
    return t;
}

int get_len(int x) {
    int ret = 0;
    while (x > 0) ++ret, x /= 10;
    return ret;
}

int main() {
    string s;
    cin >> s;

    int n = s.length();

    for (int i = 0; i < n; ++i) {
        p[i] = get_pi(s.substr(i));
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int len = j - i;
            int t = get_period(i, len);
            int add = get_len(len / t) + t;
            dp[j] = min(dp[j], dp[i] + add);
        }
    }
    printf("%d\n", dp[n]);
}
