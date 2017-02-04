#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;

vector<int> dp1(N), dp2(N);

void add(int pos, int val, vector<int>& fenw) {
    for (int i = pos; i < N; i = (i | (i + 1))) {
        fenw[i] = max(fenw[i], val);
    }
}

int getmax(int pos, vector<int>& fenw) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret = max(ret, fenw[i]);
    }
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);

        int cur = getmax(x - 1, dp1);
        add(N - x, cur + 1, dp2);
        cur = getmax(N - x - 1, dp2);
        add(x, cur + 1, dp1);
    }

    printf("%d\n", max(getmax(N - 1, dp1), getmax(N - 1, dp2)));
}
