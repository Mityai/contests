#include <bits/stdc++.h>
using namespace std;

void go(int i, int j, int& cnt, vector<string>& b, vector<char>& used) {
    int n = used.size();
    for (int k = -1; k <= 1; ++k) {
        if (cnt == 0) return;
        int newi = i + k;
        if (0 <= newi && newi < n) {
            if (!used[newi]) {
                used[newi] = true;
                char c;
                switch (k) {
                    case -1:
                        c = '\\';
                        break;
                    case 0:
                        c = '.';
                        break;
                    case 1:
                        c = '/';
                        break;
                }
                b[j - 1][newi] = c;
                --cnt;
                if (k != 0) {
                    go(newi, j - 1, cnt, b, used);
                }
            }
        }
    }
}

void solve() {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    if (a[0] == 0 || a.back() == 0) {
        puts("IMPOSSIBLE");
        return;
    }

    vector<char> used(n);
    vector<string> b(2 * n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        int j = 2 * n - 1;
        go(i, j, a[i], b, used);
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] != 0) {
            puts("IMPOSSIBLE");
            return;
        }
    }

    for (int j = b.size() - 2; j >= 0; --j) {
        if (b[j] == string(n, '.')) {
            printf("%d\n", int(b.size()) - j - 1);
            for (++j; j < b.size(); ++j) {
                printf("%s\n", b[j].c_str());
            }
            break;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++test) {
        printf("Case #%d: ", test);
        solve();
    }
}
