#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int P = 31;
const int N = 251234;

bool cmp(const pair<string, int> &a, const pair<string, int> &b) {
    return a.fi.length() < b.fi.length();
}

int main() {
    int m;
    scanf("%d", &m);

    vector< pair<string, int> > a(m);
    char s[N];
    for (int i = 0; i < m; i++) {
        scanf("%s", s);
        a[i].fi = string(s);
        a[i].se = i + 1;
    }

    sort(a.begin(), a.end(), cmp);

    unordered_map<int, int> dp, prev, num;

    int best = 0;
    for (int i = 0; i < m; i++) {
        int strhash = 0;
        for (char c : a[i].fi) {
            strhash = strhash * P + c - 'a' + 1;
        }
        dp[strhash] = 1;
        prev[strhash] = -1;
        num[strhash] = a[i].se;
        int hs = 0;
        for (int j = 0; j + 1 < (int)a[i].fi.length(); j++) {
            hs = hs * P + a[i].fi[j] - 'a' + 1;
            if (dp[strhash] < dp[hs] + 1) {
                dp[strhash] = dp[hs] + 1;
                prev[strhash] = hs;
            }
        }
        if (dp[best] < dp[strhash]) {
            best = strhash;
        }
    }
    
    vector<int> ans;
    while (best != -1) {
        ans.push_back(num[best]);
        best = prev[best];
    }

    reverse(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (int x : ans) {
        printf("%d ", x);
    }
    puts("");
}
