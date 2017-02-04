#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

ll a[12][22];

int main() {
    freopen("numbers.in", "r", stdin);
    freopen("numbers.out", "w", stdout);

    int n;
    cin >> n;
    if (n == 1) {
        cout << 9;
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        a[i][0] = 1;
    }
    a[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            a[j][i] = a[j][i-1] + (j > 0 ? a[j-1][i-1] : 0) + (j < 9 ? a[j+1][i-1] : 0);
        }
    }
    ll ans = 0;
    --n;
    for (int i = 0; i < 10; i++) {
        ans += a[i][n];
    }
    cout << ans;
    
    return 0;
}