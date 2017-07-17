#include <cstdio>
#include <chrono>
#include <random>
#include <vector>

using std::vector;
using std::max;
using std::min;

std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 100;
const int K1 = 40;
const int K2 = 40;
const int K3 = 20;

int rnd(int a, int b) {
    return rng() % (b - a + 1) + a;
}

void gen_1() {
    int n, m, k;
    do {
        n = rnd(3, 50);
        m = rnd(3, 50);
        k = rnd(3, 16);
    } while (k + 10 >= n * m);
    printf("%d %d %d\n", n, m, k);

    vector<vector<char>> used(n, vector<char>(m, false));
    for (int i = 0; i < k + k; ++i) {
        int x = rnd(0, n - 1);
        int y = rnd(0, m - 1);
        while (used[x][y]) {
            x = rnd(0, n - 1);
            y = rnd(0, m - 1);
        }
        used[x][y] = true;
        printf("%d %d\n", x, y);
    }
}

bool in(int i, int j, int n, int m) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

void gen_2() {
    int n, m, k;
    do {
        n = rnd(3, 50);
        m = rnd(3, 50);
        k = rnd(3, 16);
    } while (k + 15 >= n * m);
    printf("%d %d %d\n", n, m, k);

    vector<vector<char>> used(n, vector<char>(m, false));
    vector<int> x(k), y(k);
    for (int i = 0; i < k; ++i) {
        do {
            x[i] = rnd(0, n - 1);
            y[i] = rnd(0, m - 1);
        } while (used[x[i]][y[i]]);
        used[x[i]][y[i]] = true;
        printf("%d %d\n", x[i], y[i]);
    }

    int d = rnd(1, 4);
    for (int i = 0; i < k; ++i) {
        int fx = rnd(-d, d);
        int fy = rnd(-d, d);
        while (!in(x[i] + fx, y[i] + fy, n, m) || used[x[i] + fx][y[i] + fy]) {
            fx = rnd(-d, d);
            fy = rnd(-d, d);
        }
        used[x[i] + fx][y[i] + fy] = true;
        printf("%d %d\n", x[i] + fx, y[i] + fy);
    }
}

void gen_3() {
    int n, m, k;
    vector<int> good;
    do {
        n = rnd(3, 50);
        m = rnd(3, 50);
        k = rnd(3, 16);
        good.clear();
        for (int s = 1; s <= n; ++s) {
            if (2 * s <= std::min(n, m) && k <= 4 * (s - 1)) {
                good.push_back(s);
            }
        }
    } while (good.empty() || k + 15 >= n * m);
    printf("%d %d %d\n", n, m, k);

    vector<vector<char>> used(n, vector<char>(m, false));
    int s = good[rng() % good.size()];
    int x1, y1, x2, y2;
    do {
        x1 = rnd(0, n - s - 1);
        y1 = rnd(0, m - s - 1);
        x2 = rnd(0, n - s - 1);
        y2 = rnd(0, m - s - 1);
    } while (min(x1, x2) + s - 1 >= max(x1, x2) && min(y1, y2) + s - 1 >= max(y1, y2));

    for (int i = 0; i < k; ++i) {
        int x, y;
        do {
            x = rnd(x1, x1 + s - 1);
            y = rnd(y1, y1 + s - 1);
        } while (used[x][y]);
        used[x][y] = true;
        printf("%d %d\n", x, y);
    }

    for (int i = 0; i < k; ++i) {
        int x, y;
        do {
            x = rnd(x2, x2 + s - 1);
            y = rnd(y2, y2 + s - 1);
        } while (used[x][y]);
        used[x][y] = true;
        printf("%d %d\n", x, y);
    }
}

int main() {
    freopen("in", "w", stdout);

    for (int test = 0; test < K3; ++test) {
        gen_3();
    }

    for (int test = 0; test < K1; ++test) {
        gen_1();
    }

    for (int test = 0; test < K2; ++test) {
        gen_2();
    }
}
