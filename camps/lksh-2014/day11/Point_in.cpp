#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

const double eps = 1e-9;

double sqr(double x) {
    return x * x;
}

struct Point {
    int x, y;

    void input() {
        scanf("%d%d", &x, &y);
    }

    void out() {
        printf("%d:%d\n", x, y);
    }

    Point() {};
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    Point operator - (const Point &pt) {
        return Point(x - pt.x, y - pt.y);
    }

    bool operator < (const Point &pt) {
        return y < pt.y;
    }

    bool operator == (const Point &pt) {
        return x == pt.x && y == pt.y;
    }
};

struct Vect {
    int x, y;

    void input() {
        scanf("%d%d", &x, &y);
    }

    Vect() {};
    Vect(Point pt1, Point pt2) {
        x = pt2.x - pt1.x;
        y = pt2.y - pt1.y;
    }
};

int scal(Point pt, Point pt1, Point pt2) {
    return (pt1.x - pt.x) * (pt2.x - pt.x) + (pt1.y - pt.y) * (pt2.y - pt.y);
}

int vec(Point pt, Point pt1, Point pt2) {
    return (pt1.x - pt.x) * (pt2.y - pt.y) - (pt2.x - pt.x) * (pt1.y - pt.y);
}

struct Segment {
    int a, b, c;
    Point pt1, pt2;

    bool on_line(Point pt) {
        return scal(pt2, pt1, pt) >= 0 && scal(pt1, pt2, pt) >= 0 && vec(pt, pt1, pt2) == 0;
    }

    double getX(int y) {
        return double(-b * y - c) / double(a);
    }

    Segment() {};
    Segment(Point p1, Point p2) {
        if (p2 < p1) {
            swap(p1, p2);
        }

        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p1.y * p2.x - p2.y * p1.x;

        pt1 = p1;
        pt2 = p2;
    }
};

struct Ray {
    int a, b, c;
    Point pt_start;

    Ray() {};
    Ray(Point pt, Point pt1) {
        a = pt1.y - pt.y;
        b = pt.x - pt1.x;
        c = pt.y * pt1.x - pt1.y * pt.x;

        pt_start = pt;
    }
};

bool intersect(Segment sgm, Ray ray) {
    return (sgm.pt1.y <= ray.pt_start.y && ray.pt_start.y < sgm.pt2.y &&
            double(ray.pt_start.x) < sgm.getX(ray.pt_start.x) + eps);
}

int main() {
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);

    int n;
    scanf("%d", &n);

    Point pt;
    pt.input();

    vector<Point> pts(n);
    for (int i = 0; i < n; i++) {
        pts[i].input();
    }

    Ray ln = Ray(pt, Point(pt.x + 1, pt.y));

    bool in = false;

    for (int i = 0; i < n; i++) {
        Segment ln_tmp;
        if (i == 0) {
            ln_tmp = Segment(pts[0], pts[n - 1]);
        } else {
            ln_tmp = Segment(pts[i - 1], pts[i]);
        }
        
        if (ln_tmp.a != 0) {
            if (intersect(ln_tmp, ln)) {
                in = !in;
            }
        }

        if (ln_tmp.on_line(ln.pt_start)) {
            in = true;
            break;
        }
    }

    if (in) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}