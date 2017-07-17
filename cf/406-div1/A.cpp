#include <bits/stdc++.h>
using namespace std;

int sub(int x, int y, int n) {
    int ret = (x - y) % n;
    if (ret < 0) ret += n;
    return ret;
}

void solve(int n, vector<vector<int>>& c) {
    vector<vector<int>> who(n, vector<int>(2, -1));
    vector<vector<int>> cntloop(n, vector<int>(2));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            cntloop[i][j] = c[j].size();
        }
    }

    queue<pair<int, int>> q;
    who[n - 1][0] = who[n - 1][1] = 0;
    q.push({n - 1, 0});
    q.push({n - 1, 1});
    while (!q.empty()) {
        int v = q.front().first;
        int kem = q.front().second;
        q.pop();

        for (int x : c[1 - kem]) {
            int pos = sub(v, x, n);
            if (who[v][kem] == 0) {
                if (who[pos][1 - kem] != 1) {
                    who[pos][1 - kem] = 1;
                    q.push({pos, 1 - kem});
                }
            } else {
                --cntloop[pos][1 - kem];
                if (who[pos][1 - kem] != 1 && cntloop[pos][1 - kem] == 0) {
                    who[pos][1 - kem] = 0;
                    q.push({pos, 1 - kem});
                }
            }
        }
    }

    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            if (who[i][j] == 1) {
                printf("Win ");
            } else if (who[i][j] == 0) {
                printf("Lose ");
            } else {
                printf("Loop ");
            }
        }
        puts("");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    vector<vector<int>> a(2);
    for (int i = 0; i < 2; ++i) {
        int k;
        scanf("%d", &k);
        a[i].resize(k);
        for (int j = 0; j < k; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    solve(n, a);
}
