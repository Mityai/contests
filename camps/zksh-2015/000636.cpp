#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const double INF = 1234567890.0;

struct Point {
	double x, y;
	bool z;

	Point() {};
	Point(double x, double y) : x(x), y(y) {};
	Point(double x, double y, bool z) : x(x), y(y), z(z) {};
};

struct Line {
	double a, b, c;

	Line() {};
	Line(Point pt1, Point pt2) {
		a = pt2.y - pt1.y;
		b = pt1.x - pt2.x;
		c = - a * pt1.x - b * pt1.y;
	}
};

struct Vect {
	double x, y;

	Vect() {};
	Vect(Point pt1, Point pt2) {
		x = pt2.x - pt1.x;
		y = pt2.y - pt1.y;
	}
};

double operator & (const Vect &vc1, const Vect &vc2) {
	return vc1.x * vc2.y - vc2.x * vc1.y;
}

bool parallel(Line ln1, Line ln2) {
	double zn = (ln1.a * ln2.b - ln1.b * ln2.a);
	return zn == 0;
}

Point line_intersect(Line ln1, Line ln2) {
	double zn = (ln1.a * ln2.b - ln1.b * ln2.a);
	double x = - (ln1.c * ln2.b - ln2.c * ln1.b) / zn;
	double y = - (ln1.a * ln2.c - ln2.a * ln1.c) / zn;
	return Point(x, y);
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#endif

	int n;
	double H;
	scanf("%d%lf", &n, &H);

	Line lnH = Line(Point(0, H), Point(1, H));

	vector<Point> pts(n + 2);
	for (int i = 1; i <= n; i++) {
		double x, y;
		int z;

		scanf("%lf%lf%d", &x, &y, &z);
		pts[i] = Point(x, y, z); 
	}
	pts[0] = Point(-1, 0, false);
	pts[n + 1] = Point(1e6 + 1, 0, false);

	vector<pair<double, double> > seg(n + 2);
	{
		vector<Point> convex = {pts[0]};
		int sz = 1;

		for (int i = 1; i <= n; i++) {
			if (sz < 2) {
				convex.push_back(pts[i]);
				sz++;

				{
					Line ln = Line(convex[sz - 1], convex[sz - 2]);
					double x;
					if (parallel(ln, lnH)) {
						seg[i].fi = -INF;
						if (i == 1) {
							convex.erase(convex.begin());
							sz = 1;
						}
						continue;
					} else {
						Point inter = line_intersect(ln, lnH);
						x = inter.x;
					}

					if (x < convex[sz - 1].x) {
						seg[i].fi = x;
					} else {
						seg[i].fi = -INF;
					}
				}
				continue;
			}

			while (sz > 1) {
				if ((Vect(convex[sz - 1], convex[sz - 2]) & Vect(convex[sz - 1], pts[i])) > 0) {
					break;
				}

				convex.pop_back();
				--sz;
			}

			convex.push_back(pts[i]);
			++sz;

			{
				Line ln = Line(convex[sz - 1], convex[sz - 2]);
				double x;
				if (parallel(ln, lnH)) {
					seg[i].fi = -INF;
					continue;
				} else {
					Point inter = line_intersect(ln, lnH);
					x = inter.x;
				}

				if (x < convex[sz - 1].x) {
					seg[i].fi = x;
				} else {
					seg[i].fi = -INF;
				}
			}
		}
	}
	{
		vector<Point> convex = {pts[n + 1]};
		int sz = 1;

		for (int i = n; i >= 1; i--) {
			if (sz < 2) {
				convex.push_back(pts[i]);
				sz++;

				{
					Line ln = Line(convex[sz - 1], convex[sz - 2]);
					double x;
					if (parallel(ln, lnH)) {
						seg[i].se = INF;
						if (i == n) {
							convex.erase(convex.begin());
							sz = 1;
						}
						continue;
					} else {
						Point inter = line_intersect(ln, lnH);
						x = inter.x;
					}

					if (x > convex[sz - 1].x) {
						seg[i].se = x;
					} else {
						seg[i].se = INF;
					}
				}
				continue;
			}

			while (sz > 1) {
				if ((Vect(convex[sz - 1], convex[sz - 2]) & Vect(convex[sz - 1], pts[i])) < 0) {
					break;
				}

				convex.pop_back();
				--sz;
			}

			convex.push_back(pts[i]);
			++sz;

			{
				Line ln = Line(convex[sz - 1], convex[sz - 2]);
				double x;
				if (parallel(ln, lnH)) {
					seg[i].se = INF;
					continue;
				} else {
					Point inter = line_intersect(ln, lnH);
					x = inter.x;
				}

				if (x > convex[sz - 1].x) {
					seg[i].se = x;
				} else {
					seg[i].se = INF;
				}
			}
		}
	}

	vector<pair<double, pair<bool, int> > > all;
	for (int i = 1; i <= n; i++) {
		if (pts[i].z) {
			all.push_back({seg[i].fi, {false, i}});
			all.push_back({seg[i].se, {true, i}});
		}
	}

	sort(all.begin(), all.end());
	int ans = 0;
	set<int> q;
	for (int i = 0; i < (int)all.size(); i++) {
		int ni = all[i].se.se;
		bool op = all[i].se.fi;

		if (!op) {
			q.insert(ni);
		} else {
			if (q.find(ni) == q.end()) {
				continue;
			} else {
				++ans;
				q.clear();
			}
		}
	}

	cout << ans << endl;
}
