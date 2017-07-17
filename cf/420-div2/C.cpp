#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    set<int> q;
    vector<int> p;

    char s[15];
    int need = 1;
    int ans = 0;
    for (int i = 0; i < n + n; ++i) {
        scanf(" %s", s);

        if (s[0] == 'a') {
            int x;
            scanf("%d", &x);

            p.push_back(x);
        } else {
            if (p.empty()) {
                q.erase(q.begin());
            } else {
                if (p.back() != need) {
                    ++ans;
                    q.insert(p.begin(), p.end());
                    p.clear();
                    q.erase(q.begin());
                } else {
                    p.pop_back();
                }
            }
            ++need;
        }
    }

    printf("%d\n", ans);
}
