#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const double TL = 0.3;

inline bool isTimeLimit() {
    static int cnt = 0;
    if (++cnt == 1000) {
        cnt = 0;
        return clock() > (TL - 0.1) * CLOCKS_PER_SEC;
    }
    return false;
}

int n, k;
vector<int> a, f;
unordered_map<int, int> us;

inline void curpos(int i, int &pos1, int &pos2, int &pos3) {
    pos1 = i;
    pos2 = (i + 1) % n;
    pos3 = (i - 1) % n;
    if (pos3 < 0) pos3 += n;
}

void writeAns() {
    printf("%d\n", us[k - 1]);
    exit(0);
}

typedef pair<int, pair<int, int> > PII;
auto cmp = [](PII a, PII b) {
    return a.se.fi > b.se.fi;
};

inline void go(int A, int sum, int add, int toadd) {
    if (us.find(A) == us.end() || us[A] > sum) us[A] = sum;
    else if (us[A] <= sum) return;
    if (f[toadd] < add) return;

    if (isTimeLimit()) writeAns();

    vector<PII> all;
    for (int i = 0; i < n; i++) {
        if (!(A & (1 << i))) {
            int pos1, pos2, pos3;
            curpos(i, pos1, pos2, pos3);

            int newadd = 0;
            int cntadd = 0;
            if (!(A & (1 << pos1))) {
                newadd += a[pos1];
                cntadd++;
            }
            if (!(A & (1 << pos2))) {
                newadd += a[pos2];
                cntadd++;
            }
            if (!(A & (1 << pos3))) {
                newadd += a[pos3];
                cntadd++;
            }

            int B = A | (1 << pos1) | (1 << pos2) | (1 << pos3);
            all.push_back({B, {newadd, cntadd}});
        }
    }

    sort(all.begin(), all.end(), cmp);
    for (int i = 0; i < (int)all.size(); i++) {
        go(all[i].fi, sum + add - all[i].se.fi, add - all[i].se.fi, toadd - all[i].se.se);
    }
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
#else
    freopen("mirror.in", "r", stdin);
    freopen("mirror.out", "w", stdout);
#endif

    scanf("%d", &n);
    k = 1 << n;

    int sum = 0;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    f = a;
    sort(f.rbegin(), f.rend());
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            f[i] += f[i - 1];
        }
    }

    int A = 0;
    for (int i = 0; i < n; i++) {
        int pos1, pos2, pos3;
        curpos(i, pos1, pos2, pos3);
        int B = A | (1 << pos1) | (1 << pos2) | (1 << pos3);
        int cursum = sum - (a[pos1] + a[pos2] + a[pos3]);
        go(B, cursum, cursum, n - 3);
    }

    printf("%d\n", us[k - 1]);
}
