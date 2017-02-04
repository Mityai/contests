#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    vector< pair<string, string> > a(m);
    int cnt[m];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < m; i++) {
        cin >> a[i].fi >> a[i].se;
        for (char c : a[i].fi) cnt[i] += c - '0';
    }

    string s;
    cin >> s;

    bool used[m];
    memset(used, 0, sizeof used);

    queue<int> q;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i].fi[j] == s[j] && s[j] == '1') {
                a[i].fi[j] = '0';
                cnt[i]--;
            }
        }
        if (cnt[i] == 0) {
            q.push(i);
            used[i] = true;
        }
    }

    while (!q.empty()) {
        int k = q.front();
        q.pop();
        string t = a[k].se;

        for (int i = 0; i < n; i++) {
            if (s[i] == '0' && t[i] == '1') {
                s[i] = '1';
                for (int j = 0; j < m; j++) {
                    if (a[j].fi[i] == '1') {
                        a[j].fi[i] = '0';
                        cnt[j]--;
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            if (!used[i] && cnt[i] == 0) {
                used[i] = true;
                q.push(i);
            }
        }
    }

    cout << s << endl;
}
