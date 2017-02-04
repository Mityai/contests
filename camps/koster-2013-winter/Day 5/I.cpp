#include <iostream>
#include <cstdlib>
#include <cstdio>
#define ll long long
using namespace std;

const int md = 1000 * 1000 * 1000;

int a[2000];
ll f[2000][2000];

int main() {
    freopen("tshirts.in", "r", stdin);
    freopen("tshirts.out", "w", stdout);
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        f[i][i] = 1;
    }
    for (int k = 1; k < n; k++) {
        for (int l = 0, r = k; r < n; l++, r++) {
            if (a[l] == a[r]) {
                f[l][r] = (f[l+1][r] + f[l][r-1] + 1) % md;
            } else {
                f[l][r] = ((f[l+1][r] - f[l+1][r-1]) + f[l][r-1]) % md;
                if (f[l][r] < 0) {
                    f[l][r] += md;
                }
            }
        }
    }
    cout << f[0][--n]%md;

    return 0;
}