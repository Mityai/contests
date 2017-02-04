#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

using Point = pair<int, int>;

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, R;
        scanf("%d%d", &n, &R);

        vector<Point> pts(n);
        vector<int> xs(n), ys(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &pts[i].x, &pts[i].y);
            xs[i] = pts[i].x;
            ys[i] = pts[i].y;
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int ans = 0;
        for (int x_low : xs) {
            for (int y_low : ys) {
                int x_high = x_low + R;
                int y_high = y_low + R;
                int cur = 0;
                vector<char> took(n, false);
                for (int i = 0; i < n; ++i) {
                    if (x_low <= pts[i].x && pts[i].x <= x_high) {
                        if (y_low <= pts[i].y && pts[i].y <= y_high) {
                            took[i] = true;
                            ++cur;
                        }
                    }
                }

                int mx = 0;
                for (int a_low : xs) {
                    for (int b_low : ys) {
                        int a_high = a_low + R;
                        int b_high = b_low + R;
                        int curmx = 0;
                        for (int i = 0; i < n; ++i) {
                            if (took[i] == false) {
                                if (a_low <= pts[i].x && pts[i].x <= a_high) {
                                    if (b_low <= pts[i].y && pts[i].y <= b_high) {
                                        ++curmx;
                                    }
                                }
                            }
                        }
                        mx = max(mx, curmx);
                    }
                }

                ans = max(ans, cur + mx);
            }
        }
        printf("Case #%d: %d\n", test, ans);
    }
}
