#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
    freopen("cap.dat", "r", stdin);
    freopen("cap.sol", "w", stdout);

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int sti, stj, eni, enj;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == 'o') sti = i, stj = j;
                if (a[i][j] == '+') eni = i, enj = j;
            }
        }

        int dist[n][m];
        memset(dist, 127, sizeof dist);
        bool usedhor[n], usedver[m];
        memset(usedhor, 0, sizeof usedhor);
        memset(usedver, 0, sizeof usedver);

        const int INF = dist[0][0];
        dist[sti][stj] = 0;
        queue< pair<int, int> > q;
        q.push({sti, stj});

        while (!q.empty()) {
            auto v = q.front();
            q.pop();

            if (!usedver[v.se]) {
                for (int i = 0; i < n; i++) {
                    if (a[i][v.se] != '.') {
                        if (dist[i][v.se] > dist[v.fi][v.se] + 1) {
                            dist[i][v.se] = dist[v.fi][v.se] + 1;
                            q.push({i, v.se});
                        }
                    }
                }
            }
            usedver[v.se] = true;

            if (!usedhor[v.fi]) {
                for (int j = 0; j < m; j++) {
                    if (a[v.fi][j] != '.') {
                        if (dist[v.fi][j] > dist[v.fi][v.se] + 1) {
                            dist[v.fi][j] = dist[v.fi][v.se] + 1;
                            q.push({v.fi, j});
                        }
                    }
                }
            }
            usedhor[v.fi] = true;
        }

        if (dist[eni][enj] == INF) puts("-1");
        else printf("%d\n", dist[eni][enj]);
    }
}
