#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    //freopen("flow2.in", "r", stdin);
    //freopen("flow2.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &m, &n);

    bool a[n + 1][m + 1];
    memset(a, 0, sizeof a);

    int k;
    scanf("%d", &k);

    int ans = 0;
    for (int i = 0; i < k; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        ans = max(ans, (x2 - x1) * (y2 - y1));

        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                a[y][x] = true;
            }
        }
    }

    int up[m + 1], left[m + 1], right[m + 1];
    memset(up, -1, sizeof up);
    memset(left, -1, sizeof left);
    fill(right, right + m + 1, m + 1);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (a[i][j]) {
                up[j] = i;
            }
        }

        stack<int> q;
        while (!q.empty()) q.pop();
        for (int j = 0; j <= m; j++) {
            while (!q.empty() && up[q.top()] <= up[j]) {
                q.pop();
            }
            left[j] = -1;
            if (!q.empty()) {
                left[j] = q.top();
            }
            q.push(j);
        }

        while (!q.empty()) q.pop();
        for (int j = m; j >= 0; j--) {
            while (!q.empty() && up[q.top()] <= up[j]) {
                q.pop();
            }
            right[j] = m + 1;
            if (!q.empty()) {
                right[j] = q.top();
            }
            q.push(j);
        }

        for (int j = 0; j <= m; j++) {
            if (!a[i][j] && i - up[j] >= 1 && right[j] - left[j] >= 2) {
                ans = max(ans, (i - up[j] - 1) * (right[j] - left[j] - 2));
            }
        }
    }

    printf("%d\n", ans);
}
