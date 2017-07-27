#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("1099.in", "w", stdout);

    const int n = 222;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cout << i << ' ' << j << endl;
        }
    }
}
