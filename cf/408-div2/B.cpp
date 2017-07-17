#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<char> mark(n, false);
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        mark[x - 1] = true;
    }

    int p = 0;
    if (!mark[p]) {
        for (int i = 0; i < k; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            if (u == p) p = v;
            else if (v == p) p = u;
            if (mark[p]) {
                break;
            }
        }
    }

    printf("%d\n", p + 1);
}
