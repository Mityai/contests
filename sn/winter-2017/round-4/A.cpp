#include <bits/stdc++.h>
#define x first
#define y second
#define fi first
#define se second
using namespace std;

using ll = long long;
using Point = pair<int, int>;

struct Q {
    int x, y1, y2;
};

int main() {
#if __APPLE__
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif

    vector<pair<Point, Point>> pts(3);
    map<int, int> ys;
    set<int> xs;
    for (int i = 0; i < 3; ++i) {
        scanf("%d%d", &pts[i].fi.x, &pts[i].fi.y);
        scanf("%d%d", &pts[i].se.x, &pts[i].se.y);
        xs.insert(pts[i].fi.x);
        xs.insert(pts[i].se.x);
        ys[pts[i].fi.y] = ys[pts[i].se.y] = 0;
        ys[pts[i].fi.y + 1] = ys[pts[i].se.y + 1] = 0;
        ys[pts[i].fi.y - 1] = ys[pts[i].se.y - 1] = 0;
        if (pts[i].fi.x > pts[i].se.x) {
            swap(pts[i].fi.x, pts[i].se.x);
        }
        if (pts[i].fi.y > pts[i].se.y) {
            swap(pts[i].fi.y, pts[i].se.y);
        }
    }

    int C = 0;
    vector<int> from(100);
    for (auto& v : ys) {
        v.se = C++;
        from[C - 1] = v.fi;
    }

    for (int i = 0; i < 3; ++i) {
        pts[i].fi.y = ys[pts[i].fi.y];
        pts[i].se.y = ys[pts[i].se.y];
    }

    vector<Q> open, close;
    for (int i = 0; i < 3; ++i) {
        open.push_back({pts[i].fi.x, pts[i].fi.y, pts[i].se.y});
        close.push_back({pts[i].se.x, pts[i].fi.y, pts[i].se.y});
    }
    sort(open.begin(), open.end(), [](Q q1, Q q2) {return q1.x < q2.x;});
    sort(close.begin(), close.end(), [](Q q1, Q q2) {return q1.x < q2.x;});

    vector<int> sum(100);

    ll ans = 0;
    int i1 = 0, j1 = 0;
    int prevx = 0;
    for (int x : xs) {
        ll sumy = 0;
        ll last = -1;
        for (int i = 0; i < 98; ++i) {
            if (sum[i] > 0 && last == -1) {
                last = i;
            }
            if (sum[i] > 0 && sum[i + 1] == 0) {
                if (last != -1) {
                    sumy += from[i] - from[last];
                    last = -1;
                }
            }
        }
        ans += sumy * (x - prevx);
        prevx = x;
        while (i1 < open.size() && open[i1].x < x) ++i1;
        while (j1 < close.size() && close[j1].x < x) ++j1;
        while (i1 < open.size() && open[i1].x == x) {
            for (int j = open[i1].y1; j <= open[i1].y2; ++j) {
                ++sum[j];
            }
            ++i1;
        }
        while (j1 < close.size() && close[j1].x == x) {
            for (int j = close[j1].y1; j <= close[j1].y2; ++j) {
                --sum[j];
            }
            ++j1;
        }
    }

    cout << ans << endl;
}

