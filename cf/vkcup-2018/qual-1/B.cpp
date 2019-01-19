#include <bits/stdc++.h>

using namespace std;

int left(int pos, int k, int) {
    return max(1, pos - k);
}

int right(int pos, int k, int n) {
    return min(n, pos + k);
}

int intersect(int l_pos, int r_pos, int k, int n) {
    return max(0, right(l_pos, k, n) - left(r_pos, k, n) + 1);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> prev(n + 1);
    for (size_t i = 1; i <= n; ++i) {
        scanf("%d", &prev[i]);
    }

    vector<int> ans(n + 1);
    for (int start = 1; start <= n; ++start) {
        ans[start] = right(start, k, n) - left(start, k, n) + 1;
        if (prev[start] != 0) {
            ans[start] += ans[prev[start]] - intersect(prev[start], start, k, n);
        }
    }

    for (size_t i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    puts("");
}
