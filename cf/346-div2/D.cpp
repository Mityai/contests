#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector< pair<int, int> > a(n + 1);
    for (int i = 0; i <= n; i++) {
        scanf("%d%d", &a[i].x, &a[i].y);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int nxt = (i + 1) % n;
        int prv = i - 1;
        if (a[i].y > a[prv].y && a[nxt].x < a[i].x) ans++;
        else if (a[i].x < a[prv].x && a[nxt].y < a[i].y) ans++;
        else if (a[i].y < a[prv].y && a[nxt].x > a[i].x) ans++;
        else if (a[i].x > a[prv].x && a[nxt].y > a[i].y) ans++;
    }

    printf("%d\n", ans);
}
