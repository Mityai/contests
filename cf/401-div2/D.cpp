#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        vector<string> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        reverse(a.begin(), a.end());

        vector<int> mx(n, -1);
        mx[0] = a[0].length();
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < min(mx[i - 1], int(a[i].length())); ++j) {
                if (a[i][j] < a[i - 1][j]) {
                    mx[i] = a[i].length();
                    break;
                } else if (a[i][j] > a[i - 1][j]) {
                    mx[i] = j;
                    break;
                }
            }
            if (mx[i] == -1) {
                mx[i] = mx[i - 1];
            }
        }

        vector<string> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = a[n - i - 1].substr(0, mx[n - i - 1]);
        }

        for (string& s : ans) {
            cout << s << endl;
        }
        cout << endl;
    }
}
