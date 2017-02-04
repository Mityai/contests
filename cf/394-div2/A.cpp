#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int a, b;
    cin >> a >> b;

    if (a == 0 && b == 0) {
        cout << "NO" << endl;
    } else if (abs(a - b) <= 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
