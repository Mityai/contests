#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

vector<int> g[N];
vector<int> ans;
int mark[N];

void no() {
    puts("-1");
    exit(0);
}

bool go(int v) {
    mark[v] = 1;
    for (int u : g[v]) {
        if (mark[u] == 0) {
            if (go(u)) {
                return true;
            }
        } else if (mark[u] == 1) {
            return true;
        }
    }
    ans.push_back(v);
    mark[v] = 2;
    return false;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n, k;
    scanf("%d%d", &n, &k);

    int major[k];
    for (int i = 0; i < k; ++i) {
        scanf("%d", major + i);
        --major[i];
    }

    for (int i = 0; i < n; ++i) {
        int ti;
        scanf("%d", &ti);

        for (int j = 0; j < ti; ++j) {
            int p;
            scanf("%d", &p);
            --p;
            g[i].push_back(p);
        }
    }

    for (int i = 0; i < k; ++i) {
        int v = major[i];
        if (mark[v] == 0 && go(v)) {
            no();
        }
    }

    printf("%d\n", int(ans.size()));
    for (int x : ans) {
        printf("%d ", x + 1);
    }
    puts("");
}
