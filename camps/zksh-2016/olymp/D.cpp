#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
//asdasd
typedef long long ll;

void solve(int q) {
    const int N = 501;
    int a[N];
    memset(a, 0, sizeof a);

    for (int i = 0; i < q; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '+') {
            int x;
            scanf("%d", &x);
            a[x] = 1;
        }
        if (c == '-') {
            int x;
            scanf("%d", &x);
            a[x]--;
        }
        if (c == '?') {
            int k, d;
            scanf("%d%d", &k, &d);

            vector<int> x;
            for (int i = 0; i < N; i++) {
                if (a[i] == 1) x.push_back(i);
            }

            int n = (int)x.size();
            int ans = 0;
            for (int i = 0, j = 0; i < n; i++) {
                while (j < n && j - i + 1 < k && x[j] - x[i] <= d) {
                    j++;
                }
                if (j < n && j - i + 1 == k && x[j] - x[i] <= d) {
                    ans++;
                }
            }
            printf("%d\n", ans);
        }
    }
}

void solveq(int q) {
    set<int> s;

    for (int i = 0; i < q; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '+') {
            int x;
            scanf("%d", &x);
            s.insert(x);
        }
        if (c == '-') {
            int x;
            scanf("%d", &x);
            s.erase(x);
        }
        if (c == '?') {
            int k, d;
            scanf("%d%d", &k, &d);

            vector<int> x;
            x.reserve(s.size());
            for (int y : s) x.push_back(y);

            int n = (int)x.size();
            int ans = 0;
            for (int i = 0, j = 0; i < n; i++) {
                while (j < n && j - i + 1 < k && x[j] - x[i] <= d) {
                    j++;
                }
                if (j < n && j - i + 1 == k && x[j] - x[i] <= d) {
                    ans++;
                }
            }

            printf("%d\n", ans);
        }
    }
}

int main() {
    int q;
    scanf("%d", &q);

    if (q <= 2000) {
        solveq(q);
    } else {
        solve(q);
    }
}
