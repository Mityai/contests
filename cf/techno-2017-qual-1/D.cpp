#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int parse(string s) {
    if (s == "S") return 0;
    if (s == "M") return 1;
    if (s == "L") return 2;
    if (s == "XL") return 3;
    if (s == "XXL") return 4;
    if (s == "XXXL") return 5;
}

string to(int n) {
    if (n == 0) return "S";
    if (n == 1) return "M";
    if (n == 2) return "L";
    if (n == 3) return "XL";
    if (n == 4) return "XXL";
    if (n == 5) return "XXXL";
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<int> cnt(6);
    for (int i = 0; i < 6; i++) {
        cin >> cnt[i];
    }

    int n;
    cin >> n;

    vector<int> ans(n, -1);
    vector<pair<int, int>> tp(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int t1 = -1, t2 = -1;
        if (s.find(',') == string::npos) {
            t1 = parse(s);
        } else {
            t1 = parse(s.substr(0, s.find(',')));
            t2 = parse(s.substr(s.find(',') + 1));
        }
        if (t2 == -1) {
            if (cnt[t1] > 0) {
                ans[i] = t1;
                --cnt[t1];
            }
        }
        tp[i] = {t1, t2};
    }

    for (int i = 0; i < n; i++) {
        if (tp[i].fi == 0 && tp[i].se == 1) {
            if (cnt[0] > 0) {
                ans[i] = 0;
                --cnt[0];
            } else if (cnt[1] > 0) {
                ans[i] = 1;
                --cnt[1];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (tp[i].fi == 1 && tp[i].se == 2) {
            if (cnt[1] > 0) {
                ans[i] = 1;
                --cnt[1];
            } else if (cnt[2] > 0) {
                ans[i] = 2;
                --cnt[2];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (tp[i].fi == 2 && tp[i].se == 3) {
            if (cnt[2] > 0) {
                ans[i] = 2;
                --cnt[2];
            } else if (cnt[3] > 0) {
                ans[i] = 3;
                --cnt[3];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (tp[i].fi == 3 && tp[i].se == 4) {
            if (cnt[3] > 0) {
                ans[i] = 3;
                --cnt[3];
            } else if (cnt[4] > 0) {
                ans[i] = 4;
                --cnt[4];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (tp[i].fi == 4 && tp[i].se == 5) {
            if (cnt[4] > 0) {
                ans[i] = 4;
                --cnt[4];
            } else if (cnt[5] > 0) {
                ans[i] = 5;
                --cnt[5];
            }
        }
    }

    bool ok = true;
    for (int i = 0; i < n; i++) {
        ok &= (ans[i] != -1);
    }

    if (!ok) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << to(ans[i]) << '\n';
        }
    }
}
