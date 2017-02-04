#include <bits/stdc++.h>
#define next jkashdkashd
#define fi first
#define se second
using namespace std;

const int N = 1e5 + 1;

int next[N][26], cnt[N];
vector< pair<int, int> > relax[N];
int tc = 0;

int ans[N];

vector<int> path;

void add(string &s, vector<int> &suff) {
    int n = (int)s.length();
    int v = 0;
    path.push_back(0);
    for (int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        if (next[v][x] == -1) next[v][x] = ++tc;
        v = next[v][x];
        path.push_back(v);
        cnt[v]++;
        int depth = i + 1;
        int cursuff = suff[i];
        int up = depth - cursuff;
        if (up >= 0) {
            int u = path[up];
            relax[u].push_back({depth, cnt[v]});
        }
    }
    path.clear();
}

void go(string &t) {
    int v = 0;
    int n = (int)t.length();
    for (auto x : relax[v]) {
        if (n - x.fi - 1 >= 0) {
            ans[n - x.fi - 1] = max(ans[n - x.fi - 1], x.se);
        }
    }
    for (int i = 0; i < (int)t.length(); i++) {
        int x = t[i] - 'a';
        if (next[v][x] == -1) break;
        v = next[v][x];
        for (auto x : relax[v]) {
            if (n - x.fi - 1 >= 0) {
                ans[n - x.fi - 1] = max(ans[n - x.fi - 1], x.se);
            }
        }
    }
}

vector<int> zfunc(string &s) {
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    freopen("parades.in", "r", stdin);
    freopen("parades.out", "w", stdout);

    memset(next, -1, sizeof next);

    string t;
    cin >> t;

    int n, k;
    scanf("%d%d", &n, &k);

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    string A = "";
    reverse(t.begin(), t.end());
    A += t;
    reverse(t.begin(), t.end());
    for (int i = 0; i < n; i++) {
        reverse(s[i].begin(), s[i].end());
        A += "#" + s[i];
        reverse(s[i].begin(), s[i].end());
    }

    auto z = zfunc(A);

    vector< vector<int> > maxsuff(n);
    for (int i = 0, sum = (int)t.size() + 1; i < n; i++) {
        for (int j = sum; j - sum < (int)s[i].size(); j++) {
            maxsuff[i].push_back(z[j]);
        }
        reverse(maxsuff[i].begin(), maxsuff[i].end());
        sum += (int)s[i].size() + 1;
    }

    for (int i = 0; i < n; i++) {
        add(s[i], maxsuff[i]);
    }

    go(t);

    for (int i = 0; i < k; i++) {
        printf("%d ", ans[i]);
    }
    puts("");
}
