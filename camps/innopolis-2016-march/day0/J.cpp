#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 123;

int f[N];

void add(int pos, int val) {
    for (int i = pos; i < N; i = (i | (i + 1))) {
        f[i] += val;
    }
}

int get(int pos) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret += f[i];
    }
    return ret;
}

int main() {
    freopen("candies.in", "r", stdin);
    freopen("candies.out", "w", stdout);

    int n;
    scanf("%d", &n);

    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    a[0] = 0;

    sort(a, a + n + 1);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);

        int lb = 0, rb = n + 1;
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            int cand = a[mb] - get(mb - 1);
            if (x > cand) lb = mb;
            else rb = mb;
        }

        add(lb, 1);
        printf("%d\n", n - rb + 1);
    }

}
