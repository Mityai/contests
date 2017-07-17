#include <bits/stdc++.h>
using namespace std;

// DLRU

const string TO = "DLRU";
const int dx[] = {0, -1, 1, 0};
const int dy[] = {1, 0, 0, -1};
const map<char, char> INV({{'U', 'D'}, {'D', 'U'}, {'L', 'R'}, {'R', 'L'}});

int n, m;

bool in(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int k;
    while (cin >> n >> m >> k) {
        vector<string> a(n);
        int vi, vj;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];

            for (int j = 0; j < m; ++j) {
                if (a[i][j] == 'X') {
                    vi = i;
                    vj = j;
                    a[i][j] = '.';
                }
            }
        }

        if (k % 2 == 1) {
            cout << "IMPOSSIBLE\n";
        } else {
            string ans;
            for (int i = 0; i < k / 2; ++i) {
                for (int j = 0; j < 4; ++j) {
                    int newi = vi + dy[j];
                    int newj = vj + dx[j];
                    if (in(newi, newj) && a[newi][newj] == '.') {
                        vi = newi;
                        vj = newj;
                        ans += TO[j];
                        break;
                    }
                }
            }

            if (ans.size() != k / 2) {
                cout << "IMPOSSIBLE\n";
            } else {
                for (int i = int(ans.size()) - 1; i >= 0; --i) {
                    ans += INV.at(ans[i]);
                }
                cout << ans << endl;
            }
        }
    }
}
