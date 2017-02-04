#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

typedef long long ll;

using namespace std;

const int INF = INT_MAX;

vector<vector<int> > p;
vector<vector<int> > num;
vector<int> ans;

void no() {
    printf("infinitely kind\n");
    exit(0);
}

void rec(int l, int r) {
    if (p[l][r] == INF) {
        ans.push_back(num[l][r]);
        return;
    }

    if (l == p[l][r] || r == p[l][r]) {
        no();
    }

    rec(l, p[l][r]);
    rec(p[l][r], r);
}

int main() {
    freopen("floyd.in", "r", stdin);
    freopen("floyd.out", "w", stdout);

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<vector<int> > d(n, vector<int> (n, INF));
    num.resize(n, vector<int> (n, INF));
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);

        d[a - 1][b - 1] = -w;
        num[a - 1][b - 1] = i + 1;
    }

    vector<int> cities(k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &cities[i]);
        --cities[i];
    }

    p.resize(n, vector<int> (n, INF));
    for (int z = 0; z < n; z++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][z] < INF && d[z][j] < INF) {
                    if (d[i][j] > d[i][z] + d[z][j]) {
                        d[i][j] = d[i][z] + d[z][j];
                        p[i][j] = z;
                    }
                }
            }
        }
    }

    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < n; j++) {
            if (d[cities[i]][j] < INF && d[j][cities[i + 1]] < INF && d[j][j] < 0) {
                no();
            }
        }
        rec(cities[i], cities[i + 1]);
    }

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d ", ans[i]);
    }
}