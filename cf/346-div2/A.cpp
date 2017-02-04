#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    int ans = (a + b) % n;
    if (b < 0) {
        ans = n - abs(ans);
    }
    if (ans == 0) {
        ans = n;
    }
    cout << ans << endl;
    /*
    --a;
    cout << ((a + b) % n + n) % n + 1 << endl;*/
}
