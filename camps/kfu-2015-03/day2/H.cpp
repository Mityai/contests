#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("ate.in", "r", stdin);
    freopen("ate.out", "w", stdout);

    int n;
    while (cin >> n) {
        int ans = 0;
        for (int i = 0; i <= 99; i++) {
            int j = n - i;
            if (0 <= j && j <= 99) {
                ans++;
            }
        }
        cout << ans << endl;
    }
}
