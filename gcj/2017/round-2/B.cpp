#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, c, m;
        scanf("%d%d%d", &n, &c, &m);

        vector<vector<int>> seat(n);
        vector<int> cnt(c);
        int min_need = 0;
        for (int i = 0; i < m; ++i) {
            int p, b;
            scanf("%d%d", &p, &b);
            --p, --b;
            ++cnt[b];
            min_need = max(min_need, cnt[b]);
            seat[p].push_back(b);
        }
        for (auto& v : seat) {
            sort(v.begin(), v.end());
        }

        int lb = 0, rb = m;
        while (lb + 1 < rb) {
            int q = (lb + rb) / 2;
            if (q < min_need) {
                lb = q;
                continue;
            }
            vector<int> used(q);
            bool ok = true;
            int need = 0;
            for (int pl = 0; pl < n; ++pl) {
                vector<vector<char>> was(q, vector<char>(c, false));
                vector<char> took(q, false);
                for (int i = 0, row = 0; i < seat[pl].size(); ++i) {
                    int b = seat[pl][i];
                    int st = row;
                    while (was[row][b] || pl + 1 - used[row] == 0) {
                        ++row;
                        if (row == q) row = 0;
                        if (row == st) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) {
                        break;
                    }
                    ++used[row];
                    if (took[row]) ++need;
                    took[row] = true;
                    ++row; if (row == q) row = 0;
                }
                if (!ok) {
                    break;
                }
            }

            if (ok) {
                rb = q;
            } else {
                lb = q;
            }
        }
        int q = rb;
        int need = 0;
        {
            vector<int> used(q);
            for (int pl = 0; pl < n; ++pl) {
                vector<vector<char>> was(q, vector<char>(c, false));
                vector<char> took(q, false);
                for (int i = 0, row = 0; i < seat[pl].size(); ++i) {
                    int b = seat[pl][i];
                    while (was[row][b] || pl + 1 - used[row] == 0) {
                        ++row;
                        if (row == q) row = 0;
                    }
                    ++used[row];
                    if (took[row]) ++need;
                    took[row] = true;
                    ++row; if (row == q) row = 0;
                }
            }
        }

        printf("Case #%d: %d %d\n", test, q, need);
    }
}
