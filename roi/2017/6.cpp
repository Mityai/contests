#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t[i]);
    }

    vector<int> l(n - 1), r(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &l[i], &r[i]);
    }

    vector<int> left_lb(n), left_ub(n);
    left_lb[0] = 0;
    left_ub[0] = INF;
    for (int i = 1; i < n; ++i) {
        if (left_lb[i - 1] > l[i - 1]) {
            left_lb[i] = left_lb[i - 1];
        } else {
            left_lb[i] = max(0, l[i - 1] - t[i]);
        }
        left_ub[i] = min(left_ub[i - 1], r[i - 1]);
        if (left_ub[i] < l[i - 1]) {
            left_ub[i] = -1;
        }
    }

    vector<int> right_lb(n), right_ub(n);
    right_lb[n - 1] = 0;
    right_ub[n - 1] = INF;
    for (int i = n - 2; i >= 0; --i) {
        if (right_lb[i + 1] > l[i]) {
            right_lb[i] = right_lb[i + 1];
        } else {
            right_lb[i] = max(0, l[i] - t[i]);
        }
        right_ub[i] = min(right_ub[i + 1], r[i]);
        if (right_ub[i] < l[i]) {
            right_ub[i] = -1;
        }
    }

    for (int i = 0; i < n; ++i) {
        int ans = max(left_lb[i], right_lb[i]);
        if (ans <= min(left_ub[i], right_ub[i])) {
            printf("%d\n", ans);
        } else {
            puts("-1");
        }
    }
}
