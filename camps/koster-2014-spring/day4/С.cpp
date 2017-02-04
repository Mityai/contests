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

double dist(Point p1, Point p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    int n, m, k;
    cin >> n >> m >> k;
    vector<Point> p(n);
    int z;
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
    for (int i = 0; i < p.size(); i++) {
        a[i].y = p[i].y - zer.y;
        a[i].x = p[i].x - zer.x;

        cout << p[i].x << ':' << p[i].y << ' ' << a[i].x << ' ' << a[i].y << endl;
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
                cout << ":" << tr.x << ' '<< tr.y << endl;
                // Point p1 = p[it - a.begin()];
                // Point p2 = p[it - a.begin() - 1];
                // if (vect(tp, p1, p2) <= 0) {
                //     k--;
                // }
            }
        }
    }
    if (k <= 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}