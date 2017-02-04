#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int n, k;
vector<int> a;

ll getmax(ll cursum, const multiset<int>& seg, const multiset<int>& oth) {
    auto it1 = seg.begin();
    auto it2 = oth.rbegin();
    for (int i = 0; i != k && i != min(seg.size(), oth.size()); ++i) {
        if (*it1 < *it2) {
            cursum += *it2 - *it1;
            ++it1;
            ++it2;
        } else {
            break;
        }
    }
    return cursum;
}

int main() {
#if __APPLE__
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &k);

    a.resize(n);
    for (int& x : a) {
        scanf("%d", &x);
    }

    multiset<int> seg, oth(a.begin(), a.end());
    int ansL = 0, ansR = 0;
    ll sum = 0, ans = 0;

    for (int r = 0, st = -1; r != n; ++r) {
        sum += a[r];

        oth.erase(oth.find(a[r]));
        seg.insert(a[r]);
        ll curans = getmax(sum, seg, oth);

        if (ans < curans) {
            ans = curans;
            ansL = st + 1;
            ansR = r;
        }

        if (sum < 0) {
            for (int j = 0; j != k && r + j + 1 != n; ++j) {
                oth.erase(oth.find(a[r + j + 1]));
                sum += a[r + j + 1];
                seg.insert(a[r + j + 1]);
                curans = getmax(sum, seg, oth);
                if (ans < curans) {
                    ans = curans;
                    ansL = st + 1;
                    ansR = r + j + 1;
                }
            }
            for (int j = 0; j != k && r + j + 1 != n; ++j) {
                seg.erase(seg.find(a[r + j + 1]));
                oth.insert(a[r + j + 1]);
            }

            sum = 0;
            st = r;
            while (!seg.empty()) {
                oth.insert(*seg.begin());
                seg.erase(seg.begin());
            }
        }
    }

    vector< pair<int, int> > pos;
    set< pair<int, int> > qseg, qoth;
    for (int i = 0; i != ansL; ++i) {
        qoth.insert({a[i], i});
    }
    for (int i = ansR + 1; i != n; ++i) {
        qoth.insert({a[i], i});
    }
    for (int i = ansL; i != ansR + 1; ++i) {
        qseg.insert({a[i], i});
    }

    auto it1 = qseg.begin();
    auto it2 = qoth.rbegin();
    for (int i = 0; i != k && i != min(qseg.size(), qoth.size()); ++i) {
        if (it1->fi < it2->fi) {
            pos.push_back({it1->se, it2->se});
            ++it1;
            ++it2;
        } else {
            break;
        }
    }

    printf("%lld %d\n", ans, int(pos.size()));
    for (auto& p : pos) {
        printf("%d %d\n", p.fi + 1, p.se + 1);
    }
    printf("%d %d\n", ansL + 1, ansR + 1);
}
