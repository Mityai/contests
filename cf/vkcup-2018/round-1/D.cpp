#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

char s[N + 1], t[N + 1];

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    scanf(" %s", s);
    scanf(" %s", t);

    int n = strlen(s);
    int m = strlen(t);
    
    vector<int> cnt_s(n + 1), cnt_t(m + 1);
    for (int i = 0; i < n; ++i) {
        cnt_s[i + 1] = (s[i] != 'A');
    }
    for (int i = 0; i < m; ++i) {
        cnt_t[i + 1] = (t[i] != 'A');
    }
    partial_sum(cnt_s.begin(), cnt_s.end(), cnt_s.begin());
    partial_sum(cnt_t.begin(), cnt_t.end(), cnt_t.begin());

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int sum_s = cnt_s[b] - cnt_s[a - 1];
        int sum_t = cnt_t[d] - cnt_t[c - 1];
        char ans = ((sum_s ^ sum_t) & 1) ? '0' : '1';
        putchar(ans);
    }
    putchar('\n');
}
