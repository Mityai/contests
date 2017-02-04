#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

const int MAX_NMK = 100;

struct Point {
    int x, y, z;

    Point() {};
    Point(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

int ranks[MAX_NMK][MAX_NMK][MAX_NMK];
Point p[MAX_NMK][MAX_NMK][MAX_NMK];

bool equal(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}

void fill_parents(int n, int m, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int t = 0; t < k; t++) {
                p[i][j][t] = Point(i, j, t);
            }
        }
    }
}

Point root(Point pt) {
    if (equal(pt, p[pt.x][pt.y][pt.z])) {
        return pt;
    }

    return p[pt.x][pt.y][pt.z] = root(p[pt.x][pt.y][pt.z]);
}

void unite(Point p1, Point p2) {
    p1 = root(p1);
    p2 = root(p2);

    if (ranks[p1.x][p1.y][p1.z] > ranks[p2.x][p2.y][p2.z]) {
        swap(ranks[p1.x][p1.y][p1.z], ranks[p2.x][p2.y][p2.z]);
    }

    p[p1.x][p1.y][p1.z] = p2;

    if (ranks[p1.x][p1.y][p1.z] == ranks[p2.x][p2.y][p2.z]) {
        ++ranks[p2.x][p2.y][p2.z];
    }
}

void print(Point p1, Point p2) {
    printf("%d %d %d %d %d %d\n", p1.x + 1, p1.y + 1, p1.z + 1, p2.x + 1, p2.y + 1, p2.z + 1);
}

int main() {
    freopen("expedition.in", "r", stdin);
    freopen("expedition.out", "w", stdout);

    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);

    fill_parents(n, m, k);

    for (int ii = 0; ii < q; ii++) {
        int x_1, y_1, z_1;
        scanf("%d%d%d", &x_1, &y_1, &z_1);

        --x_1;
        --y_1;
        --z_1;

        int x_2, y_2, z_2;
        scanf("%d%d%d", &x_2, &y_2, &z_2);

        --x_2;
        --y_2;
        --z_2;

        bool swapped = false;

        if (x_1 != x_2) {
            if (x_1 < x_2) {
                for (int i = x_1 + 1; i <= x_2; i++) {
                    Point p1 = Point(i - 1, y_1, z_1);
                    Point p2 = Point(i, y_1, z_1);

                    if (equal(root(p1), root(p2))) {
                        print(p1, p2);
                    } else {
                        unite(p1, p2);
                    }
                }
            } else {
                for (int i = x_1 - 1; i >= x_2; i--) {
                    Point p1 = Point(i + 1, y_1, z_1);
                    Point p2 = Point(i, y_1, z_1);

                    if (equal(root(p1), root(p2))) {
                        print(p1, p2);
                    } else {
                        unite(p1, p2);
                    }
                }
            }
        } else if (y_1 != y_2) {
            if (y_1 < y_2) {
                for (int i = y_1 + 1; i <= y_2; i++) {
                    Point p1 = Point(x_1, i - 1, z_1);
                    Point p2 = Point(x_1, i, z_1);

                    if (equal(root(p1), root(p2))) {
                        print(p1, p2);
                    } else {
                        unite(p1, p2);
                    }
                }
            } else {
                for (int i = y_1 - 1; i >= y_2; i--) {
                    Point p1 = Point(x_1, i + 1, z_1);
                    Point p2 = Point(x_1, i, z_1);

                    if (equal(root(p1), root(p2))) {
                        print(p1, p2);
                    } else {
                        unite(p1, p2);
                    }
                }
            }
        } else if (z_1 != z_2) {
            if (z_1 < z_2) {
                for (int i = z_1 + 1; i <= z_2; i++) {
                    Point p1 = Point(x_1, y_1, i - 1);
                    Point p2 = Point(x_1, y_1, i);

                    if (equal(root(p1), root(p2))) {
                        print(p1, p2);
                    } else {
                        unite(p1, p2);
                    }
                }
            } else {
                for (int i = z_1 - 1; i >= z_2; i--) {
                    Point p1 = Point(x_1, y_1, i + 1);
                    Point p2 = Point(x_1, y_1, i);

                    if (equal(root(p1), root(p2))) {
                        print(p1, p2);
                    } else {
                        unite(p1, p2);
                    }
                }
            }
        }
    }
}