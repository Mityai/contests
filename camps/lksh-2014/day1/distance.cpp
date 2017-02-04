#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

struct Point {
	double x, y;

	void input() {
		scanf("%lf %lf", &x, &y);
	}
};

struct Line {
	double a, b, c;
	Point p1, p2;

	Line() {};
	Line(Point P1, Point P2) {
		a = P2.y - P1.y;
		b = P1.x - P2.x;
		c = P2.x * P1.y - P1.x * P2.y;

		p1 = P1;
		p2 = P2;
	}
};

double sqr(double x) {
	return x * x;
}

double dist(Point p1, Point p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

int scalar(Point p1, Point p2, Point p3) {
	double res = (p1.x - p3.x) * (p2.x - p3.x) + (p1.y - p3.y) * (p2.y - p3.y);

	if (res > 0) {
		return 1;
	} else if (res < 0) {
		return -1;
	}

	return 0;
}

double distToLine(Point p, Line l) {
	return fabs(l.a * p.x + l.b * p.y + l.c) / sqrt(sqr(l.a) + sqr(l.b));
}

double distToSegment(Point p, Line s) {
	if (scalar(p, s.p2, s.p1) >= 0 && scalar(p, s.p1, s.p2) >= 0) {
		return distToLine(p, s);
	}

	return min(dist(p, s.p1), dist(p, s.p2));
}

double distToRay(Point p, Line r) {
	if (scalar(p, r.p2, r.p1) <= 0) {
		return dist(p, r.p1);
	}

	return distToLine(p, r);
}

int main() {
    freopen("distance1.in", "r", stdin);
    freopen("distance1.out", "w", stdout);

    Point A, B, C;
    C.input();
    A.input();
    B.input();

    Line AB = Line(A, B);

    double dLine, dRay, dSeg;

    dLine = distToLine(C, AB);
    dRay = distToRay(C, AB);
    dSeg = distToSegment(C, AB);

    printf("%.7lf\n%.7lf\n%.7lf\n", dLine, dRay, dSeg);
}