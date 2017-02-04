#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;

double T, H;
double a, c;

double gety(double x) {
    return a * x * x + c;
}

double sqr(double x) {
    return x * x;
}

double dist(double fx, double fy, double sx, double sy) {
    return sqrt((fx - sx) * (fx - sx) + (fy - sy) * (fy - sy));
}

double getdist(double sy) {
    double sx = 0;
    double lb = 0, rb = T;
    for (int i = 0; i < 50; i++) {
        double mb1 = lb + (rb - lb) / 3;
        double mb2 = lb + 2 * (rb - lb) / 3;
        double f1 = dist(sx, sy, mb1, gety(mb1));
        double f2 = dist(sx, sy, mb2, gety(mb2));
        if (f1 > f2) {
            lb = mb1;
        } else {
            rb = mb2;
        }
    }
    return min(dist(sx, sy, rb, gety(rb)), min(sy, H - sy));
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    cin >> T >> H;
    if (T < eps) {
        puts("0.0000000");
        return 0;
    }
    a = - H / T / T;
    c = H;

    double lb = 0, rb = H;
    for (int i = 0; i < 50; i++) {
        double mb1 = lb + (rb - lb) / 3;
        double mb2 = lb + 2 * (rb - lb) / 3;
        double f1 = getdist(mb1), f2 = getdist(mb2);
        if (f1 < f2) {
            lb = mb1;
        } else {
            rb = mb2;
        }
    }

    printf("%.8lf\n", getdist(lb));
}
