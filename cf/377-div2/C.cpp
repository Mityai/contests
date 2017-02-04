#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;
using ull = unsigned long long;

int main() {
    ull b, d, s;
    cin >> b >> d >> s;

    ull days = max(b, max(d, s));
    if (days <= 1) {
        cout << 0 << '\n';
    } else {
        ull ans = ULLONG_MAX;
        for (int i = 0; i <= 3; i++) {
            for (int j = 0; j <= 3; j++) {
                ull curb = b;
                ull curd = d;
                ull curs = s;
                ull curans = 0;
                if (i <= 0) {
                    if (curb == 0) curans++;
                    else curb--;
                }
                if (i <= 1) {
                    if (curd == 0) curans++;
                    else curd--;
                }
                if (i <= 2) {
                    if (curs == 0) curans++;
                    else curs--;
                }
                if (j >= 1) {
                    if (curb == 0) curans++;
                    else curb--;
                }
                if (j >= 2) {
                    if (curd == 0) curans++;
                    else curd--;
                }
                if (j >= 3) {
                    if (curs == 0) curans++;
                    else curs--;
                }
                ull dd = max(curb, max(curs, curd));
                if (dd >= curb && dd >= curd && dd >= curs) {
                    curans += dd - curb;
                    curans += dd - curd;
                    curans += dd - curs;
                    ans = min(ans, curans);
                }
            }
        }
        cout << ans << '\n';
    }
}
