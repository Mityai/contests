#include <bits/stdc++.h>
using namespace std;
 
const int T = 24 * 60;
 
int main() {
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    int t[T];
    memset(t, 0, sizeof t);
 
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int h1, m1, h2, m2;
        scanf("%d%d%d%d", &h1, &m1, &h2, &m2);
        int t1 = h1 * 60 + m1;
        int t2 = h2 * 60 + m2;
        if (t1 == t2) {
            cnt++;
        } else if (t1 < t2) {
            t[t1]++;
            t[t2]--;
        } else {
            t[0]++;
            t[t2]--;
            t[t1]++;
        }
    }
 
    int ans = 0;
    for (int i = 0; i < T; i++) {
        cnt += t[i];
        if (cnt == n) {
            ans++;
        }
    }
 
    printf("%d\n", ans);
}
