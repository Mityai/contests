#include <iostream>
#include <cstdlib>
#include <cstdio>
#define ll long long
using namespace std;

int a[102][102];

int main() {
    freopen("assault.in", "r", stdin);
    freopen("assault.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] > max(a[i][j-1], max(a[i][j+1], max(a[i-1][j], a[i+1][j])))) {
                ans++;
            }
        }
    }
    cout << ans;

    return 0;
}