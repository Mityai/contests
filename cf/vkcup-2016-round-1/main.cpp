#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, d, h;
    cin >> n >> d >> h;

    if (d >= n || 2 * h < d) return 0;
    if (d == 1 && n >= 3) return 0;
    if (d == 1 && n == 2) return 0;
    for (int i = 0; i < h; i++) {
        cout << i + 1 << ' ' << i + 2 << endl;
    }
    if (d != h) cout << 1 << ' ' << h + 2 << endl;
    for (int i = 1; i < d - h; i++) {
        cout << i + h + 1 << ' ' << i + h + 2 << endl;
    }
    for (int i = d + 1; i < n; i++) {
        cout << h << ' ' << i + 1 << endl;
    }
}
