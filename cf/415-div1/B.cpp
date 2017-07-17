#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

int bound;
map<pair<int, int>, int> to;
char s[4];

bool ask(int x, int y) {
    if (x == y) return true;
    if (y > bound) return true;
    auto it = to.find({x, y});
    if (it != to.end()) {
        return it->second;
    }
    printf("1 %d %d\n", x, y);
    fflush(stdout);
    scanf(" %s", s);
    return to[{x, y}] = (s[0] == 'T');
}

int ans1 = -1, ans2 = -1;

int get(int lb, int rb) {
    while (true) {
        if (lb > rb) return -1;
        if (lb == rb) {
            if (ans1 == -1) {
                return lb;
            } else if (ask(lb, ans1)) {
                return lb;
            } else {
                return -1;
            }
        }
        int mb = (lb + rb) / 2;
        if (ask(mb, mb + 1)) {
            rb = mb;
        } else {
            lb = mb + 1;
        }
    }
}

void ans(int x, int y) {
    printf("2 %d %d\n", x, y);
    fflush(stdout);
    exit(0);
}

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    int n, k;
    scanf("%d%d", &n, &k);

    bound = n;
    ans1 = get(1, n);
    eprintf("ans1 = %d\n", ans1);
    ans2 = get(1, ans1 - 1);
    eprintf("ans2 = %d\n", ans2);
    if (ans2 == -1) ans2 = get(ans1 + 1, n);
    ans(ans1, ans2);
}

