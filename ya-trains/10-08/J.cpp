#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("J.in", "r", stdin);
    //freopen("J.out", "w", stdout);
#endif

    ll n;
    cin >> n;

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    if (n % 3 == 0) {
        cout << 0 << '\n';
        return 0;
    }

    ll k = 1;
    while ((k * 9 - 1) % n != 0) {
        ++k;
    }

    vector<int> ans(k, 9);
    ll need = n - (k * 9) % n;
    assert(need != 0);
    if (need <= 8) {
        ans.push_back(need);
    } else {
        ans.push_back(8);
        need -= 8;
        while (need >= 10) {
            ans.push_back(9);
            need -= 9;
        }
        if (need != 0) {
            ans.push_back(need);
        }
    }

    for (int i = int(ans.size()) - 1; i >= 0; --i) {
        printf("%d", ans[i]);
    }
    puts("");
}
