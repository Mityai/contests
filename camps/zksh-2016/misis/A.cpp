#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    if (n == 1) {
        puts("0 0");
        puts("0");
        return 0;
    }
    if (n == 2) {
        puts("0 0");
        puts("1 0");
        puts("0");
        return 0;
    }
    if (n == 3) {
        puts("0 0");
        puts("1 0");
        puts("0 1");
        puts("3");
        puts("1 2");
        puts("2 3");
        puts("1 3");
        return 0;
    }

    int deg[n];
    memset(deg, 0, sizeof deg);

    vector< pair<int, int> > pos(n);
    pos[0] = {0, 0};
    pos[1] = {0, 1};
    pos[2] = {0, -1};
    deg[0] = 2;
    deg[1] = 1;
    deg[2] = 1;

    int up = 1;
    int dw = 2;

    int cur = 3;
    int prev = 0;
    bool step = 0;
    int x = 1;
}
