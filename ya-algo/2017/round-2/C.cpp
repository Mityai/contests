#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);

    string s;
    cin >> s;

    map<string, vector<int>> pos;

    for (int len = 1; len <= 10; ++len) {
        for (int i = 0; i + len - 1 < s.length(); ++i) {
            pos[s.substr(i, len)].push_back(i);
        }
    }

    int q;
    cin >> q;

    for (int t = 0; t < q; ++t) {
        int l, r;
        string p;
        cin >> l >> r >> p;
        --l, --r;

        p += "*";

        bool ok = true;
        string cur;
        int p1 = -1, p2 = -1;
        for (int i = 0, curpos = l; i < p.size(); ++i) {
            if (p[i] == '*') {
                if (!cur.empty()) {
                    if (i + 1 == p.size() && p[i - 1] != '*') {
                        curpos = max(curpos, int(r - cur.size() + 1));
                    }
                    int v = lower_bound(pos[cur].begin(), pos[cur].end(), curpos) - pos[cur].begin();
                    if (v == pos[cur].size()) {
                        ok = false;
                        break;
                    }
                    if (pos[cur][v] + cur.size() - 1 <= r) {
                        curpos = pos[cur][v] + cur.size();
                        if (p1 == -1) p1 = pos[cur][v];
                        p2 = curpos;
                    } else {
                        ok = false;
                        break;
                    }
                }
                cur = "";
            } else {
                cur += p[i];
            }
        }
        if (p[0] != '*' && p1 != l) ok = false;
        if (p[p.size() - 2] != '*' && p2 != r + 1) ok = false;
        cout << (ok ? "Yes" : "No") << endl;
    }
}
