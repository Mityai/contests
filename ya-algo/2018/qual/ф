#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    vector<vector<int>> a(2 * n, vector<int>(n));
    vector<pair<int, int>> pos(n * n, {-1, -1});
    vector<int> v(n * n);
    int st;
    int p2;
    for (int i = 0; i < n + n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
            --a[i][j];
        }
        if (pos[a[i][0]].first == -1) {
            pos[a[i][0]].first = 0;
        } else {
            pos[a[i][0]].second = 0;
        }
        v[a[i][0]] = i;
        if (pos[a[i][0]] == make_pair(0, 0)) {
            st = a[i][0];
            for (int j = 0; j < i; ++j) {
                if (a[j][0] == st) {
                    p2 = j;
                    break;
                }
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        int u = i == 0 ? p2 : v[a[v[st]][i]];
        ans.insert(ans.end(), a[u].begin(), a[u].end());
    }

    for (int x : ans) {
        printf("%d ", x + 1);
    }
    puts("");
}
