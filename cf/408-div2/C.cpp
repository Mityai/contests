#include <algorithm>
#include <vector>
#include <cstdio>
#include <set>
using namespace std;

const int N = 3e5;
const int INF = 1234567890;

int a[N];
vector<int> g[N];

multiset<int> mx;
int ans = INF;

void go(int v, int p = -1) {
    mx.erase(mx.find(a[v] + 2));
    mx.insert(a[v]);
    for (int u : g[v]) {
        mx.erase(mx.find(a[u] + 2));
        mx.insert(a[u] + 1);
    }

    ans = min(ans, *mx.rbegin());

    for (int u : g[v]) {
        mx.erase(mx.find(a[u] + 1));
        mx.insert(a[u] + 2);
    }
    mx.erase(mx.find(a[v]));
    mx.insert(a[v] + 2);

    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        mx.insert(a[i] + 2);
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    go(0);
    printf("%d\n", ans);
}
