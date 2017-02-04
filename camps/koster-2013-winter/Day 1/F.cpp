#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

typedef long long ll;

const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int dist[51][51];
int n, m;
bool used[51][51];

struct Point {
    int x;
    int y;
    bool ch;
};

bool correct(Point a) {
    if (a.x >= 0 && a.y >= 0 && a.x < m && a.y < n && !used[a.x][a.y]) {
        return true;
    }
    return false;
}

int main() {
    freopen("mcs.in", "r", stdin);
    freopen("mcs.out", "w", stdout);
    
    cin >> n >> m;
    
    int sx, sy;
    cin >> sx >> sy;
    sx--; sy--;
    Point st; st.x = sx; st.y = sy; st.ch = true;

    int tx, ty;
    cin >> tx >> ty;
    tx--; ty--;

    queue<Point> q;
    q.push(st);
    used[sx][sy] = true;
    while (!q.empty()) {
        Point v = q.front();
        q.pop();
        if (v.ch) {
            for (int i = 0; i < 8; i++) {
                Point temp; temp.x = v.x + dx[i]; temp.y = v.y + dy[i];
                if (correct(temp)) {
                    dist[temp.x][temp.y] = dist[v.x][v.y] + 1;
                    used[temp.x][temp.y] = true;
                    temp.ch = !v.ch;
                    q.push(temp);
                }
            }
        } else {
            Point temp;
            temp.x = v.x - 2; temp.y = v.y;
            if (correct(temp)) {
                dist[temp.x][temp.y] = dist[v.x][v.y] + 1;
                used[temp.x][temp.y] = true;
                temp.ch = !v.ch;
                q.push(temp);
            }
            temp.x = v.x; temp.y = v.y - 2;
            if (correct(temp)) {
                dist[temp.x][temp.y] = dist[v.x][v.y] + 1;
                used[temp.x][temp.y] = true;
                temp.ch = !v.ch;
                q.push(temp);
            }
            temp.x = v.x + 2; temp.y = v.y;
            if (correct(temp)) { 
                dist[temp.x][temp.y] = dist[v.x][v.y] + 1;
                used[temp.x][temp.y] = true;
                temp.ch = !v.ch;
                q.push(temp);
            }
            temp.x = v.x; temp.y = v.y + 2;
            if (correct(temp)) {
                dist[temp.x][temp.y] = dist[v.x][v.y] + 1;
                used[temp.x][temp.y] = true;
                temp.ch = !v.ch;
                q.push(temp);
            }
        }
    }
    cout << dist[tx][ty];

    return 0;
}