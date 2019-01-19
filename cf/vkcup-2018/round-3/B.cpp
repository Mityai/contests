#include <bits/stdc++.h>
using namespace std;

struct A {
    int c, i;
};

bool cmp(const A& lhs, const A& rhs) {
    return lhs.c < rhs.c;
}

int main() {
    int n, x1, x2;
    scanf("%d%d%d", &n, &x1, &x2);

    vector<A> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].c);
        a[i].i = i;
    }

    sort(a.begin(), a.end(), cmp);

    int max_free = -1, p2 = -1;
    for (int i = 0; i < n; ++i) {
        int c2 = a[i].c;
        int cnt2 = (x2 + c2 - 1) / c2;
        if (i + cnt2 <= n) {
            if (max_free < n - i - cnt2) {
                max_free = n - i - cnt2;
                p2 = i;
            }
        }

        int c1 = a[i].c;
        int cnt1 = (x1 + c1 - 1) / c1;
        if (i + cnt1 <= n) {
            if (i + cnt1 < n && a[i + cnt1].c * 1ll * (n - i - cnt1) >= x2) {
                puts("Yes");
                vector<int> ans1, ans2;
                for (int j = i; j < i + cnt1; ++j) {
                    ans1.push_back(a[j].i);
                }
                for (int j = i + cnt1, sum = 0; sum < x2; ++j) {
                    ans2.push_back(a[j].i);
                    sum += a[j].c;
                }
                printf("%d %d\n", (int)ans1.size(), (int)ans2.size());
                for (int x : ans1) {
                    printf("%d ", x + 1);
                }
                putchar('\n');
                for (int x : ans2) {
                    printf("%d ", x + 1);
                }
                putchar('\n');
                return 0;
            }
            if (max_free >= cnt1) {
                puts("Yes");
                vector<int> ans1, ans2;
                for (int j = i; j < i + cnt1; ++j) {
                    ans1.push_back(a[j].i);
                }
                int sum = 0;
                for (int j = p2; sum < x2; ++j) {
                    if (j == i) j = i + cnt1;
                    ans2.push_back(a[j].i);
                    sum += a[p2].c;
                }
                printf("%d %d\n", (int)ans1.size(), (int)ans2.size());
                for (int x : ans1) {
                    printf("%d ", x + 1);
                }
                putchar('\n');
                for (int x : ans2) {
                    printf("%d ", x + 1);
                }
                putchar('\n');
                return 0;
            }
        }
    }

    puts("No");
}
