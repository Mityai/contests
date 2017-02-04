#include <bits/stdc++.h>
using namespace std;

const int N = 3e3;

const int P = 29;
int p[N];

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("prof.in", "r", stdin);
    freopen("prof.out", "w", stdout);
#endif

    string s;
    cin >> s;

    int n = (int)s.length();
    
    vector<int> hs(n);
    p[0] = 1;
    hs[0] = s[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
        hs[i] = hs[i - 1] * P + s[i] - 'a' + 1;
        p[i] = p[i - 1] * P;
    }

    unordered_map<int, int> q(n);
    int ans = 0;
    for (int len = 0; len < n; len++) {
        q.clear();
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            int curh = hs[r] - (l > 0 ? hs[l - 1] * p[r - l + 1] : 0);
            if (q.find(curh) != q.end()) {
                if (q[curh] + len < l) {
                    ans++;
                    q[curh] = n;
                }
            } else {
                q[curh] = l;
            }
        }
    }
    printf("%d\n", ans);
}
