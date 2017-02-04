#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;
using ull = unsigned long long;

const int MOD1 = 1e9 + 9;
const int MOD2 = 1e9 + 7;
const ll P = 31;
const int F = 32;
const int N = 2123;

char s[N];

int K, W, Q;

int gethash() {
    int ret1 = 0;
    for (int i = 0; i != strlen(s); ++i) {
        char c = s[i];
        ret1 = (ret1 * P + tolower(c) - 'a') % MOD1;
    }
    return ret1;
}

vector<ull> split() {
    vector<ull> ret((int(strlen(s)) + 63) / 64);
    for (int i = 0; i != strlen(s); ++i) {
        int bit = (tolower(s[i]) != s[i]);
        int num = i / 64;
        int pos = i - num * 64;
        ret[num] |= (bit << pos);
    }
    return ret;
}

bool diff(vector<ull>& a, vector<ull>& b) {
    if (a.size() != b.size()) return false;
    int cnt = 0;
    for (int i = 0; i != a.size(); ++i) {
        cnt += __builtin_popcountll(a[i] ^ b[i]);
        if (cnt > K) return false;
    }
    return true;
}

int main() {
#if __APPLE__
    freopen("5.in", "r", stdin);
    freopen("5.out", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scanf("%d%d", &K, &W);

    unordered_map<int, vector< vector<ull> > > X;
    for (int i = 0; i != W; ++i) {
        scanf("%s", s);
        int hs = gethash();
        X[hs].push_back(split());
    }

    int Q;
    scanf("%d", &Q);

    for (int i = 0; i != Q; ++i) {
        scanf("%s", s);

        int curhs = gethash();
        auto curvc = split();
        int ans = 0;
        for (auto& vc : X[curhs]) {
            ans += diff(vc, curvc);
        }
        printf("%d\n", ans);
    }
}
