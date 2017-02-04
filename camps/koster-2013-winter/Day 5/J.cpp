#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

int a[1001];
bool f[101][50001];
int pathx[101][50001], pathy[101][50001];

int main() {
    freopen("zerosum.in", "r", stdin);
    freopen("zerosum.out", "w", stdout);
    
    int n;
    cin >> n;
    int all = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        all += a[i];
    }
    f[1][-a[1]+all] = 1;
    f[1][a[1]+all] = 1;
    pathx[1][-a[1]+all] = -a[1]+all;
    pathy[1][-a[1]+all] = 0;
    pathx[1][a[1]+all] = a[1]+all;
    pathy[1][a[1]+all] = 0;
    int lastx = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 2*all; j++) {
            f[i][j] = (j+a[i] <= 2*all ? f[i-1][j+a[i]] : 0) || (j-a[i] >= 0 ? f[i-1][j-a[i]] : 0);
            if (f[i][j]) {
                if (j+a[i] <= 2*all ? f[i-1][j+a[i]] : 0) {
                    pathx[i][j] = j+a[i];
                } else {
                    pathx[i][j] = j-a[i];
                }
                pathy[i][j] = i-1;
            }
        }
    }
    string ans = "";
    int j = all; int i = n;
    while (i != 1) {
        if (pathx[i][j] < j) {
            ans += '+';
        } else {
            ans += '-';
        }
        int j1 = j, i1 = i;
        i = pathy[i1][j1];
        j = pathx[i1][j1];
    }
    if (pathx[1][j] < all) {
        ans += '-';
    } else {
        ans += '+';
    }
    for (int i = n-1; i >= 0; i--) {
        cout << ans[i];
    }    

    return 0;
}