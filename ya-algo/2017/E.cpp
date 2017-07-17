#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("E.in", "r", stdin);
    //freopen("E.out", "w", stdout);
#endif

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);

    if (dx > dy) {
        swap(x1, y1);
        swap(x2, y2);
        swap(dx, dy);
    }

    int ans = dx + dx;
    dy -= dx;
    ans += dy + dy - dy % 2;
    cout << ans << endl;
}
