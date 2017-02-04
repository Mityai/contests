#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 10;
vector<string> a(N);
bool used[N][N];
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

pair<int, int> go(int i, int j) {
    used[i][j] = true;
    for (int k = 0; k != 4; k++) {
        int newi = i + dx[k];
        int newj = j + dy[k];
        if (0 <= newi && newi < N) {
            if (0 <= newj && newj < N) {
                if (a[newi][newj] == 'x') {
                    if (!used[newi][newj]) {
                        return go(newi, newj);
                    }
                }
            }
        }
    }
    return {i, j};
}

int main() {
    for (int i = 0; i != N; ++i) {
        cin >> a[i];
    }

    vector<pair<pair<int, int>, pair<int, int>>> ans;
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            if (a[i][j] == 'x') {
                if (!used[i][j]) {
                    auto en = go(i, j);
                    ans.push_back({{i, j}, {en.fi, en.se}});
                }
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto x : ans) {
        cout << x.fi.fi + 1 << ' ' << x.fi.se + 1 << ' ' << x.se.fi + 1 << ' ' << x.se.se + 1 << '\n';
    }
}
