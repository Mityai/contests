#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

const int N = 5500;
const int INF = INT_MAX;

vector<int> E[N];
int flow[N], cap[N], to[N];
bool used[N];

const int s = 0, t = N - 1;

int e = 0;
void addEdge(int v, int u, int c) {
    assert(u < N && v < N);
    E[v].push_back(e);
    E[u].push_back(e ^ 1);

    cap[e] = c;
    cap[e ^ 1] = 0;

    to[e] = u;
    to[e ^ 1] = v;

    e += 2;
}

int push(int v, int cur_flow, int min_flow) {
    if (v == t || cur_flow == 0) {
        return cur_flow;
    }
    used[v] = true;
    for (int edge : E[v]) {
        if (!used[to[edge]] && cap[edge] - flow[edge] >= min_flow) {
            int a = push(to[edge], min(cur_flow, cap[edge] - flow[edge]), min_flow);
            if (a > 0) {
                flow[edge] += a;
                flow[edge ^ 1] -= a;
                return a;
            }
        }
    }
    return 0;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("tea.in", "r", stdin);
    freopen("tea.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int d;
        scanf("%d", &d);

        addEdge(n + i, n + i + m, d);
        addEdge(n + i + m, t, INF);
    }

    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);

        for (int j = 0; j < k; j++) {
            int tea;
            scanf("%d", &tea);

            addEdge(i, n + tea, INF);
        }

        addEdge(s, i, INF);
    }

    int l = 0, r = (int)1e8 + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        for (int edge : E[s]) {
            if (!(edge & 1)) {
                cap[edge] = mid;
            }
        }

        memset(flow, 0, sizeof flow);
        int sum = 0;
        for (int i = (1 << 30);; i >>= 1) {
            while (true) {
                memset(used, 0, sizeof used);
                int cur = push(s, INF, i);
                if (cur == 0) break;
                sum += cur;
            }
            if (i == 0) break;
        }

        if (mid * n == sum) {
            l = mid;
        } else {
            r = mid;
        }
    }

    printf("%d\n", l);
}
