#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);

    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    for (int test = 1; test <= t; ++test) {
        int r, c;
        cin >> r >> c;

        vector<string> s(r + 2, string(c + 2, '#'));
        vector<pair<int, int>> p;
        for (int i = 1; i <= r; ++i) {
            cin >> s[i];
            s[i] = "#" + s[i] + "#";
            for (int j = 1; j <= c; ++j) {
                if (s[i][j] == '-' || s[i][j] == '|') {
                    p.push_back({i, j});
                }
            }
        }
        for (int i = 0; i <= c + 1; ++i) {
            s[0][i] = s[r + 1][i] = '#';
        }
        for (int j = 0; j <= r + 1; ++j) {
            s[j][0] = s[j][c + 1] = '#';
        }

        vector<pair<int, int>> all;
        bool imp = false;
        for (auto& v : p) {
            int i = v.fi;
            int j = v.se;
            bool ok1, ok2;
            {
                bool ok = true;
                for (int k = i - 1; k >= 0; --k) {
                    if (s[k][j] == '|' || s[k][j] == '-') {
                        ok = false;
                        break;
                    } else if (s[k][j] == '#') {
                        break;
                    }
                }
                if (ok) {
                    for (int k = i + 1; k <= r + 1; ++k) {
                        if (s[k][j] == '|' || s[k][j] == '-') {
                            ok = false;
                            break;
                        } else if (s[k][j] == '#') {
                            break;
                        }
                    }
                }
                ok1 = ok;
            }
            {
                bool ok = true;
                for (int k = j - 1; k >= 0; --k) {
                    if (s[i][k] == '|' || s[i][k] == '-') {
                        ok = false;
                        break;
                    } else if (s[i][k] == '#') {
                        break;
                    }
                }
                if (ok) {
                    for (int k = j + 1; k <= c + 1; ++k) {
                        if (s[i][k] == '|' || s[i][k] == '-') {
                            ok = false;
                            break;
                        } else if (s[i][k] == '#') {
                            break;
                        }
                    }
                }
                ok2 = ok;
            }
            if (ok1 && ok2) {
                all.push_back({i, j});
            } else if (ok1) {
                s[i][j] = '|';
                for (int k = i - 1; k >= 0; --k) {
                    if (s[k][j] == '#') break;
                    s[k][j] = '$';
                }
                for (int k = i + 1; k <= r; ++k) {
                    if (s[k][j] == '#') break;
                    s[k][j] = '$';
                }
            } else if (ok2) {
                s[i][j] = '-';
                for (int k = j - 1; k >= 0; --k) {
                    if (s[i][k] == '#') break;
                    s[i][k] = '$';
                }
                for (int k = j + 1; k <= c; ++k) {
                    if (s[i][k] == '#') break;
                    s[i][k] = '$';
                }
            } else {
                imp = true;
                break;
            }
        }
        cout << "Case #" << test << ": ";
        if (imp) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }

        bool ok = false;
        vector<string> ans;
        for (int mask = 0; mask < (1 << all.size()); ++mask) {
            auto a = s;
            for (int i = 0; i < all.size(); ++i) {
                int j = ((mask >> i) & 1);
                int pi = all[i].fi;
                int pj = all[i].se;
                if (j == 1) {
                    a[pi][pj] = '|';
                    for (int k = pi - 1; k >= 0; --k) {
                        if (a[k][pj] == '#') break;
                        a[k][pj] = '$';
                    }
                    for (int k = pi + 1; k <= r; ++k) {
                        if (a[k][pj] == '#') break;
                        a[k][pj] = '$';
                    }
                } else {
                    a[pi][pj] = '-';
                    for (int k = pj - 1; k >= 0; --k) {
                        if (a[pi][k] == '#') break;
                        a[pi][k] = '$';
                    }
                    for (int k = pj + 1; k <= c; ++k) {
                        if (a[pi][k] == '#') break;
                        a[pi][k] = '$';
                    }
                }
            }
            bool here = true;
            for (int i = 1; i <= r; ++i) {
                for (int j = 1; j <= c; ++j) {
                    if (a[i][j] == '.') {
                        here = false;
                        break;
                    }
                }
                if (!here) break;
            }
            if (here) {
                ans = a;
                ok = true;
                break;
            }
        }
        if (ok) {
            cout << "POSSIBLE" << '\n';
            for (int i = 1; i <= r; ++i) {
                for (int j = 1; j <= c; ++j) {
                    if (ans[i][j] == '$') ans[i][j] = '.';
                    cout << ans[i][j];
                }
                cout << endl;
            }
        } else {
            cout << "IMPOSSIBLE" << '\n';
        }
    }
}
