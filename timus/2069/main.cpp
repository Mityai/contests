#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
    }

    int ans = 0;
    int max_col = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[max_col]) {
            max_col = i;
        }
    }
    if (max_col == 0) {
        ans = max(ans, min(a[0], b[m - 1]));
    } else if (max_col == n - 1) {
        ans = max(ans, min(a[n - 1], b[0]));
    } else {
        ans = max(ans, min(a[max_col], min(b[0], b[m - 1])));
    }

    int max_row = 0;
    for (int i = 1; i < m; ++i) {
        if (b[i] > b[max_row]) {
            max_row = i;
        }
    }
    if (max_row == 0) {
        ans = max(ans, min(b[0], a[n - 1]));
    } else if (max_row == m - 1) {
        ans = max(ans, min(b[m - 1], a[0]));
    } else {
        ans = max(ans, min(b[max_row], min(a[0], a[n - 1])));
    }

    printf("%d\n", ans);
}
