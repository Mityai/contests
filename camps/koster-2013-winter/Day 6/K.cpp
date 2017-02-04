#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

int a[51][51];

int main() {
    freopen("knight.in", "r", stdin);
    freopen("knight.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    a[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            a[i][j] = a[i-2][j-1] + a[i-1][j-2];
        }
    }
    cout << a[n][m];

    return 0;
}