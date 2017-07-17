#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        pos[x - 1] = i;
    }

    int ans = 1;
    for (int i = 0, cur = 0; i < n; ++i) {
        if (cur > pos[i]) {
            ++ans;
        }
        cur = pos[i];
    }

    printf("%d\n", ans);
}
