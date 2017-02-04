#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 5 * 30 * 2 + 100;
//const int N = 50;
const int M = N / 2;

int A[N][N];

struct F {
    int i, j;
    int dx, dy;
};

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }

    vector<vector<int>> pole(N, vector<int>(N));
    queue<F> q;
    q.push({M, M, 0, 1});

    for (int i = 0; i < n; i++) {
        queue<F> p;
        set<pair<pair<int, int>, pair<int, int>>> was;
        while (!q.empty()) {
            auto v = q.front();
            q.pop();

            for (int j = 0; j < t[i]; j++) {
                A[v.i + v.dx * j][v.j + v.dy * j] = true;
            }

            F f1, f2;
            int newx = v.i + v.dx * (t[i] - 1);
            int newy = v.j + v.dy * (t[i] - 1);
            if (mp(v.dx, v.dy) == mp(1, 0)) {
                f1 = {newx, newy, 1, 1};
                f2 = {newx, newy, 1, -1};
            }
            if (mp(v.dx, v.dy) == mp(1, -1)) {
                f1 = {newx, newy, 1, 0};
                f2 = {newx, newy, 0, -1};
            }
            if (mp(v.dx, v.dy) == mp(0, -1)) {
                f1 = {newx, newy, 1, -1};
                f2 = {newx, newy, -1, -1};
            }
            if (mp(v.dx, v.dy) == mp(-1, -1)) {
                f1 = {newx, newy, -1, 0};
                f2 = {newx, newy, 0, -1};
            }
            if (mp(v.dx, v.dy) == mp(-1, 0)) {
                f1 = {newx, newy, -1, 1};
                f2 = {newx, newy, -1, -1};
            }
            if (mp(v.dx, v.dy) == mp(-1, 1)) {
                f1 = {newx, newy, 0, 1};
                f2 = {newx, newy, -1, 0};
            }
            if (mp(v.dx, v.dy) == mp(0, 1)) {
                f1 = {newx, newy, -1, 1};
                f2 = {newx, newy, 1, 1};
            }
            if (mp(v.dx, v.dy) == mp(1, 1)) {
                f1 = {newx, newy, 0, 1};
                f2 = {newx, newy, 1, 0};
            }
            f1.i += f1.dx;
            f1.j += f1.dy;
            f2.i += f2.dx;
            f2.j += f2.dy;
            if (was.find({{f1.i, f1.j}, {f1.dx, f1.dy}}) == was.end()) {
                was.insert({{f1.i, f1.j}, {f1.dx, f1.dy}});
                p.push(f1);
            }
            if (was.find({{f2.i, f2.j}, {f2.dx, f2.dy}}) == was.end()) {
                was.insert({{f2.i, f2.j}, {f2.dx, f2.dy}});
                p.push(f2);
            }
        }
        q.swap(p);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ans += A[i][j];
        }
    }

    printf("%d\n", ans);
}
