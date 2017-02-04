#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
 
struct Point {
    int x, y;
};

struct Reb {
    int y, x;
};

int vect(Point p, Point p1, Point p2) {
    double k = (p1.x - p.x) * (p2.y - p.y) - (p2.x - p.x) * (p1.y - p.y);
    if (k > 0) return 1;
    if (k < 0) return -1;
    return 0;
}

int main() {
    freopen("theodore.in", "r", stdin);
    freopen("theodore.out", "w", stdout);
 
    int n, m, k;
    cin >> n >> m >> k;
    vector<Point> p(n);
    int z = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        if (p[i].x < p[z].x || (p[i].x == p[z].x && p[i].y < p[z].y)) {
            z = i;
        }
    }
    Point zer = p[z];
    rotate(p.begin(), p.begin() + z, p.end());
    p.erase(p.begin());
    vector<Reb> a(p.size());
    vector<double> kt(p.size());
    for (int i = 0; i < p.size(); i++) {
        a[i].y = p[i].y - zer.y;
        a[i].x = p[i].x - zer.x;
        kt[i] = atan2(double(a[i].y), double(a[i].x));
    }
    for (int i = 0; i < m; i++) {
        Point tp;
        cin >> tp.x >> tp.y;
        if (tp.x >= zer.x) {
            if (tp.x == zer.x && tp.y == zer.y) {
                k--;
            } else {
                Reb tr;
                tr.y = tp.y - zer.y;
                tr.x = tp.x - zer.x;
                double tgk;
                tgk = atan2(double(tr.y), double(tr.x));
                vector<double>::iterator it = upper_bound(kt.begin(), kt.end(), tgk);
                if (it == kt.end() && tgk == kt[kt.size()-1]) {
                    --it;
                }
                Point p1 = p[it - kt.begin()];
                Point p2 = p[it - kt.begin() - 1];
                if (it != kt.begin()) {
                    if ((vect(tp, zer, p2) >= 0 && vect(tp, p2, p1) >= 0 && vect(tp, p1, zer) >= 0) ||
                        (vect(tp, zer, p2) <= 0 && vect(tp, p2, p1) <= 0 && vect(tp, p1, zer) <= 0)) {
                        k--;
                    }
                }
            }
        }
        if (k == 0) {
            cout << "YES";
            return 0;
        }
    }
    if (k <= 0)
        cout << "YES";
    else
        cout << "NO";
}