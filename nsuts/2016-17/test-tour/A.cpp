#include <bits/stdc++.h>

using namespace std;

int main() {
#if !__APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    long long n;
    cin >> n;

    if (n >= 1) {
        cout << n * (n + 1) / 2 << endl;
    } else {
        n = abs(n);
        cout << 1 - n * (n + 1) / 2 << endl;
    }
}
