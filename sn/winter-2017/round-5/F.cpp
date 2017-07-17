#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int ask(int l, int r) {
    int x = (1 << (r + 1)) - 1 - ((1 << l) - 1);
    cout << "? " << x << endl;
    cout.flush();
    int ret;
    cin >> ret;
    return ret;
}

int cnt1;
int ans;

int go(int l, int r, int cnt = -1) {
    if (cnt == -1) {
        cnt = ask(l, r);
        if (l == 0 && r == 15) cnt = cnt1 = 16 - cnt;
        else cnt = -(cnt - cnt1 - (r - l + 1)) / 2;
    }

    if (r == l) {
        if (cnt == 1) {
            ans |= (1 << l);
        }
    } else {
        int m = (l + r) / 2;
        int left = go(l, m);
        go(m + 1, r, cnt - left);
    }

    return cnt;
}

int main() {
    go(0, 15);
    cout << "! " << ans << endl;
    cout.flush();
}
