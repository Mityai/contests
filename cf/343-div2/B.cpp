#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 366 + 2;

int main() {
    int n;
    scanf("%d", &n);

    int fame[N], male[N];
    memset(fame, 0, sizeof fame);
    memset(male, 0, sizeof male);
    for (int i = 0; i < n; i++) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        if (c == 'M') {
            male[a]++;
            male[b + 1]--;
        } else {
            fame[a]++;
            fame[b + 1]--;
        }
    }

    int ans = 0;
    int m = 0, f = 0;
    for (int i = 1; i < N; i++) {
        m += male[i];
        f += fame[i];
        ans = max(ans, min(m, f));
    }
    cout << ans * 2 << endl;
}
