#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    string n;
    char x, y;
    cin >> n >> x >> y;
    swap(x, y);

    bool less = false;
    string ans(n.size() - 1, x);
    if (n[0] >= y) {
        bool less = false;
        int lastx = 0;
        string another(n.size(), y);
        for (int i = 0; i < n.size(); ++i) {
            if (less) {
                another[i] = x;
            } else {
                if (n[i] < y) {
                    i = lastx;
                    less = true;
                    another[i] = y;
                } else if (n[i] >= x) {
                    lastx = i;
                    if (n[i] > x) {
                        less = true;
                    }
                    another[i] = x;
                } else if (n[i] >= y) {
                    if (n[i] > y) {
                        less = true;
                    }
                    another[i] = y;
                }
            }
        }
        bool ok = true;
        less = false;
        if (another[0] != '0') {
            for (int i = 0; i < n.size(); ++i) {
                if (another[i] != x && another[i] != y) {
                    ok = false;
                    break;
                }
                if (!less) {
                    if (another[i] > n[i]) {
                        ok = false;
                        break;
                    } else {
                        if (another[i] < n[i]) {
                            less = true;
                        }
                    }
                }
            }
            if (ok) ans = another;
        }
    }

    if (ans.empty()) ans = "-1";

    cout << ans << endl;
}
