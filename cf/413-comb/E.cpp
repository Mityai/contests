#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e17;

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &c[i]);
        }

        int na;
        scanf("%d", &na);

        vector<char> ida(n, false);
        for (int i = 0; i < na; ++i) {
            int x;
            scanf("%d", &x);
            --x;
            ida[x] = true;
        }

        int nb;
        scanf("%d", &nb);

        vector<char> idb(n, false);
        for (int i = 0; i < nb; ++i) {
            int x;
            scanf("%d", &x);
            --x;
            idb[x] = true;
        }

        if (k > m) {
            puts("-1");
            continue;
        }

        vector<int> both, ina, inb, no;
        for (int i = 0; i < n; ++i) {
            if (ida[i] && idb[i]) {
                both.push_back(c[i]);
            } else if (ida[i]) {
                ina.push_back(c[i]);
            } else if (idb[i]) {
                inb.push_back(c[i]);
            } else {
                no.push_back(c[i]);
            }
        }

        sort(both.begin(), both.end());
        sort(ina.begin(), ina.end());
        sort(inb.begin(), inb.end());
        sort(no.begin(), no.end());

        ll sumboth = 0;
        for (int i = 0; i < both.size(); ++i) {
            sumboth += both[i];
        }
        int love1 = both.size();
        int love2 = both.size();
        int i1 = 0, j1 = 0;
        ll suma = 0, sumb = 0;
        while (love1 < k && i1 < ina.size()) {
            ++love1;
            suma += ina[i1];
            ++i1;
        }
        while (love2 < k && j1 < inb.size()) {
            ++love2;
            sumb += inb[j1];
            ++j1;
        }

        if (love1 < k || love2 < k) {
            puts("-1");
            continue;
        }

        int cnt = love1 + love2 - (int)both.size();
        ll sumoth = 0;
        int k1 = 0;
        while (cnt < m && k1 < no.size()) {
            sumoth += no[k1];
            ++cnt;
            ++k1;
        }

        if (cnt != m) {
            puts("-1");
            continue;
        }

        ll ans = sumboth + suma + sumb + sumoth;
        for (int cnt_both = (int)both.size() - 1; cnt_both >= 0; --cnt_both) {
            sumboth -= both[cnt_both];
            --love1;
            --love2;
            --cnt;
            if (i1 < ina.size()) {
                ++love1;
                ++cnt;
                suma += ina[i1];
                ++i1;
            }
            if (j1 < inb.size()) {
                ++love2;
                ++cnt;
                sumb += inb[j1];
                ++j1;
            }
            if (love1 < k || love2 < k) {
                break;
            }
            while (cnt > m && k1 > 0) {
                --cnt;
                --k1;
                sumoth -= no[k1];
            }
            while (cnt < m && k1 < no.size()) {
                ++cnt;
                sumoth += no[k1];
                ++k1;
            }
            if (cnt != m) {
                break;
            }
            ans = min(ans, sumboth + suma + sumb + sumoth);
        }
        printf("%lld\n", ans);
    }
}
