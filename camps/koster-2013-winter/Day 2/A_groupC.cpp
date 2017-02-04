#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

int n;

bool so_close(int x1, int x2, int x3, int y1, int y2, int y3) {
    return (abs(x1-y1) <= 2 || abs(x1-y1) >= n-2) && 
           (abs(x2-y2) <= 2 || abs(x2-y2) >= n-2) && 
           (abs(x3-y3) <= 2 || abs(x3-y3) >= n-2);
}

int main() {
    freopen("combo.in", "r", stdin);
    freopen("combo.out", "w", stdout);

    cin >> n;
    int x1, x2, x3;
    cin >> x1 >> x2 >> x3;
    int y1, y2, y3;
    cin >> y1 >> y2 >> y3;
    
    int ans = 0;
    for (int n1 = 1; n1 <= n; n1++) {
        for (int n2 = 1; n2 <= n; n2++) {
            for (int n3 = 1; n3 <= n; n3++) {
                if (so_close(n1, n2, n3, x1, x2, x3) || so_close(n1, n2, n3, y1, y2, y3)) {
                    ans++;
                }
            }
        }
    }
    cout << ans;

    return 0;
}