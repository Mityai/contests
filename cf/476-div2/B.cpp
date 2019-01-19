#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    // freopen("B.in", "r", stdin);
    // freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> fam(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            const int di[] = {1, 0};
            const int dj[] = {0, 1};
            for (int dir = 0; dir < 2; ++dir) {
                bool ok = true;
                for (int t = 0; t < k; ++t) {
                    if (i + di[dir] * t >= n || j + dj[dir] * t >= n) {
                        ok = false;
                        break;
                    }
                    if (a[i + di[dir] * t][j + dj[dir] * t] != '.') {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    for (int t = 0; t < k; ++t) {
                        ++fam[i + di[dir] * t][j + dj[dir] * t];
                    }
                }
            }
        }
    }

    int b_i = 0, b_j = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fam[i][j] > fam[b_i][b_j]) {
                b_i = i;
                b_j = j;
            }
        }
    }

    cout << b_i + 1 << ' ' << b_j + 1 << endl;
}
