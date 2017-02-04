#include <bits/stdc++.h> 
#define fi first
#define se second
using namespace std;

using ll = long long;

struct Seg {
    int x1, y1, x2, y2;
};

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);

    vector<Seg> ver, hor;
    for (int i = 0; i < n; i++) {
        Seg s;
        scanf("%d%d%d%d", &s.x1, &s.y1, &s.x2, &s.y2);
        if (s.x1 > s.x2) swap(s.x1, s.x2);
        if (s.y1 > s.y2) swap(s.y1, s.y2);
        if (s.x1 == s.x2) {
            ver.push_back(s);
        } else {
            hor.push_back(s);
        }
    }

    ll ans = 0;
    for (int i = 0; i < (int)hor.size(); i++) {
        for (int j = i + 1; j < (int)hor.size(); j++) {
            ll cnt = 0;
            int y1 = min(hor[i].y1, hor[j].y1);
            int y2 = max(hor[i].y2, hor[j].y2);
            for (int k = 0; k < (int)ver.size(); k++) {
                if (hor[i].x1 <= ver[k].x1 && ver[k].x1 <= hor[i].x2) {
                    if (hor[j].x1 <= ver[k].x1 && ver[k].x1 <= hor[j].x2) {
                        if (ver[k].y1 <= y1 && y2 <= ver[k].y2) {
                            cnt++;
                        }
                    }
                }
            }
            ans += cnt * (cnt - 1) / 2;
        }
    }
    printf("%lld\n", ans);
}
