#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;

int a[501][501], f[501][501];

int main() {
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 0) {
                f[i][j] = 0;
            } else {
                f[i][j] = min(f[i][j-1], min(f[i-1][j], f[i-1][j-1]))+1;
            }
            ans = max(f[i][j], ans);
        }
    }
    cout << ans;

    return 0;
}