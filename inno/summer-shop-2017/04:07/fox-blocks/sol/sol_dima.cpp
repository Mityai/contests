#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e9 + 12345;
const int MOD = 1e9 + 7;
const int N = 3e5 + 12;
const int K = 19;

int up_left[K][N];
int up_right[K][N];
int sum_left[K][N];
int sum_right[K][N];

int main() {
    // freopen("fox-blocks.in", "r", stdin);
    // freopen("fox-blocks.out", "w", stdout);

    int n, t;
    scanf("%d%d", &n, &t);

    vector<ll> h(n + 2);
    h[0] = h[n + 1] = INF;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &h[i]);
    }

    vector<ll> pref(n + 2);
    partial_sum(h.begin(), h.end(), pref.begin());

    {
        stack<int> q;
        q.push(0);
        up_left[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            while (!q.empty() && h[q.top()] < h[i]) {
                q.pop();
            }
            up_left[0][i] = q.top();
            ll free_area = (i - q.top() - 1) * h[i];
            free_area -= pref[i - 1] - pref[q.top()];
            free_area %= MOD;
            sum_left[0][i] = free_area;
            q.push(i);
        }
    }
    {
        stack<int> q;
        q.push(n + 1);
        up_right[0][n + 1] = n + 1;
        for (int i = n; i >= 1; --i) {
            while (!q.empty() && h[q.top()] <= h[i]) {
                q.pop();
            }
            up_right[0][i] = q.top();
            ll free_area = (q.top() - i - 1) * h[i];
            free_area -= pref[q.top() - 1] - pref[i];
            free_area %= MOD;
            sum_right[0][i] = free_area;
            q.push(i);
        }
    }

    for (int i = 1; i < K; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            up_left[i][j] = up_left[i - 1][up_left[i - 1][j]];
            up_right[i][j] = up_right[i - 1][up_right[i - 1][j]];
            sum_left[i][j] = (sum_left[i - 1][j] + sum_left[i - 1][up_left[i - 1][j]]) % MOD;
            sum_right[i][j] = (sum_right[i - 1][j] + sum_right[i - 1][up_right[i - 1][j]]) % MOD;
        }
    }

    int sumans = 0;
    for (int ii = 0; ii < t; ++ii) {
        int a, b;
        scanf("%d%d", &a, &b);

        int ans = 0;
        int v = a;
        for (int i = K - 1; i >= 0; --i) {
            if (up_right[i][v] <= b) {
                ans = (ans + sum_right[i][v]) % MOD;
                v = up_right[i][v];
            }
        }
        v = b;
        for (int i = K - 1; i >= 0; --i) {
            if (up_left[i][v] >= a) {
                ans = (ans + sum_left[i][v]) % MOD;
                v = up_left[i][v];
            }
        }
        sumans = (sumans + ans) % MOD;
    }

    printf("%d\n", sumans);
}
