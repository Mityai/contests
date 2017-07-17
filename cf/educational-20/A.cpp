#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> a(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j && k >= 1) {
                a[i][j] = 1;
                --k;
            } else if (k >= 2) {
                a[i][j] = a[j][i] = 1;
                k -= 2;
            }
        }
    }

    if (k > 0) {
        puts("-1");
    } else {
        for (auto& v : a) {
            for (int x : v) {
                printf("%d ", x);
            }
            puts("");
        }
    }
}
