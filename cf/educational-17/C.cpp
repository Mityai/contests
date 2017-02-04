#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    int n = a.length();
    int m = b.length();

    int nxt[n][26], prev[n][26];
    memset(nxt, -1, sizeof nxt);
    memset(prev, -1, sizeof prev);

    for (int i = n - 1; i >= 0; --i) {
        if (i + 1 < n) {
            for (int j = 0; j < 26; ++j) {
                nxt[i][j] = nxt[i + 1][j];
            }
        }
        nxt[i][a[i] - 'a'] = i;
    }

    for (int i = 0; i < n; ++i) {
        if (i - 1 >= 0) {
            for (int j = 0; j < 26; ++j) {
                prev[i][j] = prev[i - 1][j];
            }
        }
        prev[i][a[i] - 'a'] = i;
    }

    int end[m];
    memset(end, -1, sizeof end);

    for (int i = 0; i < m; ++i) {
        if (i == 0) {
            end[i] = nxt[0][b[i] - 'a'];
        } else {
            end[i] = end[i - 1];
            if (end[i] != -1) {
                if (end[i] == n - 1) {
                    end[i] = -1;
                } else {
                    end[i] = nxt[end[i] + 1][b[i] - 'a'];
                }
            }
        }
    }

    int start[m];
    memset(start, -1, sizeof start);

    for (int i = m - 1; i >= 0; --i) {
        if (i == m - 1) {
            start[i] = prev[n - 1][b[i] - 'a'];
        } else {
            start[i] = start[i + 1];
            if (start[i] != -1) {
                if (start[i] == 0) {
                    start[i] = -1;
                } else {
                    start[i] = prev[start[i] - 1][b[i] - 'a'];
                }
            }
        }
    }

    int ansi = -1, ansj = m;
    for (int i = 0; i < m; ++i) {
        if (start[i] != -1) {
            ansi = -1;
            ansj = i;
            break;
        }
    }

    for (int i = m - 1; i >= 0; --i) {
        if (end[i] != -1 && i + 1 > m - ansj) {
            ansi = i;
            ansj = m;
            break;
        }
    }

    for (int i = 1, j = 0; i < m; ++i) {
        while (j + 1 < i && end[j + 1] != -1 && end[j + 1] < start[i]) {
            ++j;
        }
        if (end[j] < start[i] && start[i] != -1 && end[j] != -1) {
            if (m - i + j > m - ansj + ansi) {
                ansi = j;
                ansj = i;
            }
        }
    }

    string ans = b.substr(0, ansi + 1) + b.substr(ansj);
    if (ans.empty()) {
        cout << "-" << endl;
    } else {
        cout << ans << endl;
    }
}
