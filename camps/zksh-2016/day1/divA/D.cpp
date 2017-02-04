#include <bits/stdc++.h>
#define left hflasdhkjf
#define right asdfklas
#define prev asdhakl
#define fi first
#define se second
using namespace std;

const int N = 5e4;
const int INF = 1234567890;

int dp[N + 1], left[N + 1], right[N + 1];
int prev[N + 1], leftid[N + 1], rightid[N + 1], down[N + 1];

struct Point {
    int x, y, id;
};

bool cmpx(Point &a, Point &b) {
    return a.x < b.x;
}

bool cmpy(Point &a, Point &b) {
    return a.y < b.y;
}

int upper_bound_y(vector<Point> &a, int y) {
    int lb = -1, rb = (int)a.size();
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        if (a[mb].y <= y) lb = mb;
        else rb = mb;
    }
    return rb;
}

int lower_bound_y(vector<Point> &a, int y) {
    int lb = -1, rb = (int)a.size();
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        if (a[mb].y < y) lb = mb;
        else rb = mb;
    }
    return lb;
}

int upper_bound_x(vector<Point> &a, int x) {
    int lb = -1, rb = (int)a.size();
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        if (a[mb].x <= x) lb = mb;
        else rb = mb;
    }
    return rb;
}

int lower_bound_x(vector<Point> &a, int x) {
    int lb = -1, rb = (int)a.size();
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        if (a[mb].x < x) lb = mb;
        else rb = mb;
    }
    return lb;
}

main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<Point> a(n + 1);
    map< int, vector<Point> > ver, hor, di1, di2;
    a[n] = {0, 0, n};
    hor[a[n].x].push_back(a[n]);
    ver[a[n].y].push_back(a[n]);
    di1[a[n].x - a[n].y].push_back(a[n]);
    di2[a[n].y + a[n].x].push_back(a[n]);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].id = i;
        hor[a[i].x].push_back(a[i]);
        ver[a[i].y].push_back(a[i]);
        di1[a[i].x - a[i].y].push_back(a[i]);
        di2[a[i].x + a[i].y].push_back(a[i]);
    }

    for (auto &q : ver) {
        sort(q.se.begin(), q.se.end(), cmpx);
    }
    for (auto &q : hor) {
        sort(q.se.begin(), q.se.end(), cmpy);
    }
    for (auto &q : di1) {
        sort(q.se.begin(), q.se.end(), cmpx);
    }
    for (auto &q : di2) {
        sort(q.se.begin(), q.se.end(), cmpx);
    }

    vector< vector<int> > g(n);
    for (int i = 0; i < n; i++) {
        int x = a[i].x, y = a[i].y;
        {
            auto &vec = hor[x];
            int p = lower_bound_y(vec, y);
            if (p != -1 && p != (int)vec.size()) {
                g[a[i].id].push_back(vec[p].id);
            }
        }
        {
            auto &vec = di1[x - y];
            int p = lower_bound_x(vec, x);
            if (p != -1 && p != (int)vec.size()) {
                g[a[i].id].push_back(vec[p].id);
            }
        }
        {
            auto &vec = di2[x + y];
            int p = upper_bound_x(vec, x);
            if (p != -1 && p != (int)vec.size()) {
                g[a[i].id].push_back(vec[p].id);
            }
        }
    }

    memset(dp, -1, sizeof dp);
    memset(left, -1, sizeof left);
    memset(right, -1, sizeof right);
    memset(prev, -1, sizeof prev);
    memset(leftid, -1, sizeof leftid);
    memset(rightid, -1, sizeof rightid);
    memset(down, -1, sizeof down);

    dp[n] = 0;
    for (auto &it : ver) {
        if (it.fi == 0) continue;
        auto vec = it.se;
        for (Point pt : vec) {
            int id = pt.id;
            for (int pr : g[id]) {
                if (dp[id] < dp[pr] + 1 && dp[pr] != -1) {
                    prev[id] = pr;
                    down[id] = pr;
                    dp[id] = dp[pr] + 1;
                }
            }
        }
        for (int i = 0, mx = -INF, mxid = -1; i < (int)vec.size(); i++) {
            int id = vec[i].id;
            leftid[id] = mxid;
            left[id] = mx + i;
            if (mx < dp[id] && dp[id] != -1) {
                mx = dp[id];
                mxid = id;
            }
        }
        for (int i = (int)vec.size() - 1, mx = -INF, mxid = -1; i >= 0; i--) {
            int id = vec[i].id;
            rightid[id] = mxid;
            right[id] = mx + (int)vec.size() - i - 1;
            if (mx < dp[id] && dp[id] != -1) {
                mx = dp[id];
                mxid = id;
            }
        }
        for (int i = 0; i < (int)vec.size(); i++) {
            int id = vec[i].id;
            if (left[id] > dp[id] && left[id] > right[id]) {
                dp[id] = left[id];
                prev[id] = leftid[id];
            } else if (right[id] > dp[id] && right[id] > left[id]) {
                dp[id] = right[id];
                prev[id] = rightid[id];
            } 
        }
    }

    int v = n;
    for (int i = 0; i < n; i++) {
        if (dp[v] < dp[i]) {
            v = i;
        }
    }

    vector<int> ans;
    while (v != n) {
        ans.push_back(v);
        int p = prev[v];
        int yp = a[v].y;
        if (a[v].y == a[p].y) {
            auto &vec = ver[a[v].y];
            int pos1, pos2;
            for (int i = 0; i < (int)vec.size(); i++) {
                if (vec[i].id == a[v].id) pos1 = i;
                if (vec[i].id == a[p].id) pos2 = i;
            }
            if (pos2 < pos1) {
                for (int i = pos1 - 1; i > pos2; i--) {
                    ans.push_back(vec[i].id);
                }
                for (int i = 0; i <= pos2; i++) {
                    ans.push_back(vec[i].id);
                }
            } else {
                for (int i = pos1 + 1; i < pos2; i++) {
                    ans.push_back(vec[i].id);
                }
                for (int i = (int)vec.size() - 1; i >= pos2; i--) {
                    ans.push_back(vec[i].id);
                }
            }
            v = down[p];
        } else {
            v = p;
        }
    }
    
    reverse(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); i++) {
        printf("%d ", ans[i] + 1);
    }
    puts("");
}
