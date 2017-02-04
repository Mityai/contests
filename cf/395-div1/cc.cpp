
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

struct Rect {
    int x1, y1;
    int x2, y2;
    int i;
};

const int N = 5e5;
int C = 0;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<Rect> rc(n);
    vector<int> col(n, -1);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &rc[i].x1, &rc[i].y1, &rc[i].x2, &rc[i].y2);
        rc[i].i = i;
    }

    unordered_map<int, vector<Rect>> lb, rb, ub, db;
    for (int i = 0; i < n; ++i) {
        lb[rc[i].x1].push_back(rc[i]);
        rb[rc[i].x2].push_back(rc[i]);
        ub[rc[i].y1].push_back(rc[i]);
        db[rc[i].y2].push_back(rc[i]);
    }

    for (auto& v : lb) {
        auto& ar = v.se;
        sort(ar.begin(), ar.end(), [](Rect& r1, Rect& r2) { return r1.y1 < r2.y1; });
    }
    for (auto& v : rb) {
        auto& ar = v.se;
        sort(ar.begin(), ar.end(), [](Rect& r1, Rect& r2) { return r1.y1 < r2.y1; });
    }
    for (auto& v : ub) {
        auto& ar = v.se;
        sort(ar.begin(), ar.end(), [](Rect& r1, Rect& r2) { return r1.x1 < r2.x1; });
    }
    for (auto& v : db) {
        auto& ar = v.se;
        sort(ar.begin(), ar.end(), [](Rect& r1, Rect& r2) { return r1.x1 < r2.x1; });
    }

    for (int i = 0; i < n; ++i) {
        vector<char> used(4, false);
        {
            auto& vec = lb[rc[i].x2];
            int lb = -1, rb = vec.size();
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if (vec[mb].y2 <= rc[i].y1) lb = mb;
                else rb = mb;
            }
            for (int j = rb; j < vec.size(); ++j) {
                if (max(vec[j].y1, rc[i].y1) < min(vec[j].y2, rc[i].y2)) {
                    if (col[vec[j].i] != -1) {
                        used[col[vec[j].i]] = true;
                    }
                } else break;
            }
        }
        {
            auto& vec = rb[rc[i].x1];
            int lb = -1, rb = vec.size();
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if (vec[mb].y2 <= rc[i].y1) lb = mb;
                else rb = mb;
            }
            for (int j = rb; j < vec.size(); ++j) {
                if (max(vec[j].y1, rc[i].y1) < min(vec[j].y2, rc[i].y2)) {
                    if (col[vec[j].i] != -1) {
                        used[col[vec[j].i]] = true;
                    }
                } else break;
            }
        }
        {
            auto& vec = ub[rc[i].y2];
            int lb = -1, rb = vec.size();
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if (vec[mb].x2 <= rc[i].x1) lb = mb;
                else rb = mb;
            }
            for (int j = rb; j < vec.size(); ++j) {
                if (max(vec[j].x1, rc[i].x1) < min(vec[j].x2, rc[i].x2)) {
                    if (col[vec[j].i] != -1) {
                        used[col[vec[j].i]] = true;
                    }
                } else break;
            }
        }
        {
            auto& vec = db[rc[i].y1];
            int lb = -1, rb = vec.size();
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if (vec[mb].x2 <= rc[i].x1) lb = mb;
                else rb = mb;
            }
            for (int j = rb; j < vec.size(); ++j) {
                if (max(vec[j].x1, rc[i].x1) < min(vec[j].x2, rc[i].x2)) {
                    if (col[vec[j].i] != -1) {
                        used[col[vec[j].i]] = true;
                    }
                } else break;
            }
        }
        for (int c = 0; c < 4; ++c) {
            if (used[c] == false) {
                col[i] = c;
                break;
            }
        }
    }

    puts("YES");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", col[i] + 1);
    }
}
