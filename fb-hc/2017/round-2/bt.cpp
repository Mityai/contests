#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

double getarea(double x1, double h1, double x2, double h2) {
    double rx = x1 + h1;
    double lx = x2 - h2;
    double mx = (lx + rx) * 0.5;
    double mh = mx - lx;
    double ret = 0;
    if (mh < 0) {
        ret += h1 * h1 * 0.5;
        ret += h2 * h2 * 0.5;
    } else {
        ret += 0.5 * (mx - x1) * (mh + h1);
        ret += 0.5 * (x2 - mx) * (mh + h2);
    }
    return ret;
}

bool lefthigher(double x1, double h1, double x2, double h2) {
    double dx = x2 - x1;
    double dh = h1 - dx;
    return dh > h2;
}

bool righthigher(double x1, double h1, double x2, double h2) {
    double dx = x2 - x1;
    double dh = h2 - dx;
    return dh > h1;
}

int main() {
    freopen("bt.in", "r", stdin);
    freopen("bt.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n;
        scanf("%d", &n);

        vector<int> x(n), h(n);
        int Ax, Bx, Cx;
        int Ah, Bh, Ch;
        scanf("%d%d%d%d", &x[0], &Ax, &Bx, &Cx);
        scanf("%d%d%d%d", &h[0], &Ah, &Bh, &Ch);
        
        for (int i = 1; i < n; ++i) {
            x[i] = (Ax * 1ll * x[i - 1] + Bx) % Cx + 1;
            h[i] = (Ah * 1ll * h[i - 1] + Bh) % Ch + 1;
        }

        /*
        for (int i = 0; i < n; ++i) {
            cout << x[i] << ":" << h[i] << ' ';
        }
        cout << endl;*/

        set<pair<double, double>> pts;
        pts.insert({-1e9, 0});
        pts.insert({1e9, 0});
        double area = 0;
        double ans = 0;
        for (int i = 0; i < n; ++i) {
            auto left = --pts.lower_bound({x[i], h[i]});
            while (true) {
                if (righthigher(left->fi, left->se, x[i], h[i])) {
                    --left;
                } else {
                    break;
                }
            }
            auto right = pts.lower_bound({x[i], h[i]});
            while (true) {
                if (lefthigher(x[i], h[i], right->fi, right->se)) {
                    ++right;
                } else {
                    break;
                }
            }

            // TODO NIZHE

            double curp = 0;
            auto prev = left;
            auto cur = left; ++cur;
            int steps = 0;
            while (prev != right) {
                curp += getarea(prev->fi, prev->se, cur->fi, cur->se);
                ++prev;
                ++cur;
                ++steps;
            }
            area -= curp;

            if (lefthigher(left->fi, left->se, x[i], h[i]) || righthigher(x[i], h[i], right->fi, right->se)) {
                area += getarea(left->fi, left->se, right->fi, right->se);
                if (steps > 1) {
                    pts.erase(++left, right);
                }
            } else {
                area += getarea(left->fi, left->se, x[i], h[i]);
                area += getarea(x[i], h[i], right->fi, right->se);
                if (steps > 1) {
                    pts.erase(++left, right);
                }
                pts.insert({x[i], h[i]});
            }

            //cout << "area " << i + 1 << ' ' << area << endl;
            ans += area;
        }

        printf("Case #%d: %.10lf\n", test, ans);
    }
}
