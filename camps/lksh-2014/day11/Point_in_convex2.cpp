#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
         
#define mp make_pair
#define fi first
#define se second

typedef long long ll;

const double eps = 1e-7;
const int INF = 123456789;
const int MaXN = 100000;

struct Point {
 	int x, y;
	
	void in() {
     	scanf("%d%d", &x, &y);
	}
};

vector<Point> a;
int n, m;

int vect(const Point &pt, const Point &pt1, const Point &pt2) {
 	int x1 = (pt1.x - pt.x) * (pt2.y - pt.y);
	int x2 = (pt2.x - pt.x) * (pt1.y - pt.y);
	
	return x1 - x2;
}

bool point_in_poly(const Point &pt) {
	int l = 1, r = n - 1;
    while (l <= r) {
     	int mid = (l + r) >> 1;
		if (vect(a[0], pt, a[mid]) <= 0) {
			r = mid - 1;
		} else {
         	l = mid + 1;
		}
	}

	if (l < 2 || vect(a[0], pt, a[n - 1]) >= 0 || vect(a[l], pt, a[l - 1]) >= 0) {
     	return false;
	}

	return true;
}

int main() {
	scanf("%d", &n);

	a.resize(n);
	for (int i = 0; i < n; i++) {
     	a[i].in();
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		Point B;
		B.in();
		
		if (!point_in_poly(B)) {
			printf("NO\n");
			return 0;
		}
	}

	printf("YES\n");
}
