#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
   
    int b[n];
    memset(b, 0, sizeof b);

    ll ans = 1;

    bool one = false;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            one = true;
            ll cnt = 0;
            for (int j = i - 1; j >= 0; j--) {
                if (a[j] == 1) {
                    ans *= (cnt + 1);
                    cnt = 0;
                    break;
                }
                cnt++;
            }
        }
    }

    if (!one) cout << 0 << endl;
    else cout << ans << endl;
}
