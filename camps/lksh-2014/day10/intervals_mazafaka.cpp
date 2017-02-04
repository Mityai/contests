#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>

#define pb push_back

typedef long long ll;

using namespace std;

const long double eps = 1e-8;

long double sqr(long double x) {
    return x * x;
}

long double _min(long double x, long double y) {
    if (x < y - eps) {
        return x;
    }

    return y;
}

long double _max(long double x, long double y) {
    if (x > y + eps) {
        return x;
    }
    
    return y;
}

struct Point {
    long double x, y;

    void input() {
        cin >> x >> y;
    }

    void print() {
        cout.precision(12);
        cout << fixed << x << ' ' << y;
    }

    Point() {};
    Point(long double _x, long double _y) {
        x = _x;
        y = _y;
    }

    Point operator - (const Point &pt) {
        return Point(x - pt.x, y - pt.y);
    }

    bool operator == (const Point &pt) {
        return abs(x - pt.x) < eps && abs(y - pt.y) < eps;
    }

    bool operator != (const Point &pt) {
        return abs(x - pt.x) > eps || abs(y - pt.y) > eps;
    }

    bool operator < (const Point &pt) {
        return x < pt.x - eps || (abs(x - pt.x) < eps && y < pt.y - eps);
    }

    bool operator > (const Point &pt) {
        return x > pt.x + eps || (abs(x - pt.x) < eps && y > pt.y + eps);
    }
};

struct Vect {
    long double x, y;

    void input() {
        cin >> x >> y;
    }

    Vect() {};
    Vect(Point pt1, Point pt2) {
        x = pt2.x - pt1.x;
        y = pt2.y - pt1.y;
    }
};

struct Interval {
    long double a, b, c;
    Point pt1, pt2;

    void norm() {
        long double sqrt_ab = sqrt(sqr(a) + sqr(b));
        if (abs(sqrt_ab) > eps) {
            a /= sqrt_ab;
            b /= sqrt_ab;
            c /= sqrt_ab;
        }
    }

    void input() {
        pt1.input();
        pt2.input();

        if (pt2 < pt1) {
            swap(pt1, pt2);
        }

        a = pt1.y - pt2.y;
        b = pt2.x - pt1.x;
        c = -a * pt1.x - b * pt1.y;

        norm();
    }

    bool on_line(Point pt) {
        return abs(a * pt.x + b * pt.y + c) < eps;
    }

    bool pt_in(Point pt) {
        return pt1 != pt && pt2 != pt && 
               _min(pt1.x, pt2.x) < pt.x + eps && pt.x < _max(pt1.x, pt2.x) + eps &&
               _min(pt1.y, pt2.y) < pt.y + eps && pt.y < _max(pt1.y, pt2.y) + eps;
    }
};

Point intersect(Interval AB, Interval CD) {
    Point pt;
    long double zn = CD.a * AB.b - AB.a * CD.b;

    pt.x = (AB.c * CD.b - CD.c * AB.b) / zn;
    pt.y = (AB.a * CD.c - CD.a * AB.c) / zn;

    return pt;
}

bool intersect_coor(double a, double b, double c, double d) {
    if (b < a - eps) {
        swap(a, b);
    }

    if (d < c - eps) {
        swap(c, d);
    }

    return _max(a, c) < _min(b, d) + eps;
}

bool intersect_pts(Point pt1, Point pt2, Point pt3, Point pt4) {
    return intersect_coor(pt1.x, pt2.x, pt3.x, pt4.x) &&
           intersect_coor(pt1.y, pt2.y, pt3.y, pt4.y);
}

bool parallel(Interval AB, Interval CD) {
    return abs(AB.a * CD.b - CD.a * AB.b) < eps;
}

void empty() {
    cout << "Empty" << endl;
}

void print_point(Point pt) {
    cout << "Point ";
    pt.print();
    cout << endl;
}

void print_interval(Point pt1, Point pt2) {
    cout << "Interval ";
    pt1.print();
    cout << " ";
    pt2.print();
    cout << endl;
}

int main() {
    freopen("segments.in", "r", stdin);
    freopen("segments.out", "w", stdout);

    int n;
    cin >> n;

    for (int ii = 0; ii < n; ii++) {
        Interval AB, CD;
        AB.input();
        CD.input();

        if (AB.pt1 == AB.pt2 || CD.pt1 == CD.pt2) {
            empty();
            continue;
        }

        if (!intersect_pts(AB.pt1, AB.pt2, CD.pt1, CD.pt2)) {
            empty();
            continue;
        }

        if (!parallel(AB, CD)) {
            Point pt = intersect(AB, CD);

            if (AB.pt_in(pt) && CD.pt_in(pt)) {
                print_point(pt);
            } else {
                empty();
            }            
        } else {
            if (!AB.on_line(CD.pt1) || !AB.on_line(CD.pt2)) {
                empty();
                continue;
            }

            Point pt1, pt2;
            if (AB.pt1 > CD.pt1) {
                pt1 = AB.pt1;
            } else {
                pt1 = CD.pt1;
            }

            if (AB.pt2 < CD.pt2) {
                pt2 = AB.pt2;
            } else {
                pt2 = CD.pt2;
            }

            if (pt1 > pt2) {
                swap(pt1, pt2);
            }

            if (pt1 != pt2) {
                print_interval(pt1, pt2);
            } else {
                empty();
            }
        }
    }
}