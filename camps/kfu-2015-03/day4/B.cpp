#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("subpair.in", "r", stdin);
    freopen("subpair.out", "w", stdout);

    string s, t;
    while (cin >> s >> t) {
        int n = (int)s.length();
        int m = (int)t.length();
        s = "#" + s + "*";
        t = "$" + t + "%";

        int f[n + 1][m + 1];
        memset(f, 0, sizeof f);
        int e[n + 1][m + 1];
        memset(e, 0, sizeof e);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i] == t[j]) {
                    f[i][j] = f[i - 1][j - 1] + 1;
                    if (f[i][j] == 1) e[i][j] = i;
                    else e[i][j] = e[i - 1][j - 1];
                }
            }
        }

        int bestf[n + 1][m + 1];
        memset(bestf, 0, sizeof bestf);
        int beste[n + 1][m + 1];
        memset(beste, 0, sizeof beste);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (f[i][j] > bestf[i][j - 1] && f[i][j] > bestf[i - 1][j]) {
                    bestf[i][j] = f[i][j];
                    beste[i][j] = e[i][j];
                } else if (bestf[i][j - 1] > bestf[i - 1][j]) {
                    bestf[i][j] = bestf[i][j - 1];
                    beste[i][j] = beste[i][j - 1];
                } else {
                    bestf[i][j] = bestf[i - 1][j];
                    beste[i][j] = beste[i - 1][j];
                }
            }
        }

        int g[n + 2][m + 2];
        memset(g, 0, sizeof g);

        int q[n + 2][m + 2];
        memset(q, 0, sizeof q);

        for (int i = n; i >= 1; i--) {
            for (int j = m; j >= 1; j--) {
                if (s[i] == t[j]) {
                    g[i][j] = g[i + 1][j + 1] + 1;
                    q[i][j] = i;
                }
            }
        }

        int bestg[n + 2][m + 2];
        memset(bestg, 0, sizeof bestg);
        int bestq[n + 2][m + 2];
        memset(bestq, 0, sizeof bestq);

        for (int i = n; i >= 1; i--) {
            for (int j = m; j >= 1; j--) {
                if (g[i][j] > bestg[i][j + 1] && g[i][j] > bestg[i + 1][j]) {
                    bestg[i][j] = g[i][j];
                    bestq[i][j] = q[i][j];
                } else if (bestg[i][j + 1] > bestg[i + 1][j]) {
                    bestg[i][j] = bestg[i][j + 1];
                    bestq[i][j] = bestq[i][j + 1];
                } else {
                    bestg[i][j] = bestg[i + 1][j];
                    bestq[i][j] = bestq[i + 1][j];
                }
            }
        }

        int ansi = 0, ansj = 0, ansleni = 0, anslenj = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (bestf[i][j] + bestg[i + 1][j + 1] > ansleni + anslenj) {
                    ansleni = bestf[i][j];
                    anslenj = bestg[i + 1][j + 1];
                    ansi = beste[i][j];
                    ansj = bestq[i + 1][j + 1];
                }
            }
        }

        printf("%s\n%s\n", s.substr(ansi, ansleni).c_str(), s.substr(ansj, anslenj).c_str());
    }
}
