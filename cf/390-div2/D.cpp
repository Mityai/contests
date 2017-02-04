#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

struct Seg {
    int a, b;
    int id;
};

int main() {
    int n, k;
    while (scanf("%d%d", &n, &k) == 2) {
        vector<Seg> seg(n);
        for (size_t i = 0; i < n; ++i) {
            scanf("%d%d", &seg[i].a, &seg[i].b);
            seg[i].id = i;
        }

        sort(seg.begin(), seg.end(), [](Seg& a, Seg& b) {return a.a < b.a;});

        multiset<int> rborder;
        int left = 0, right = -1;
        for (int i = 0; i < n; i++) {
            int curleft = seg[i].a;
            rborder.insert(seg[i].b);
            while (rborder.size() > k) {
                rborder.erase(rborder.begin());
            }
            int curright = *rborder.begin();
            if (rborder.size() == k && right - left < curright - curleft) {
                left = curleft;
                right = curright;
            }
        }

        printf("%d\n", right - left + 1);
        if (right - left == -1) right = INT_MIN, left = INT_MAX;
        vector<int> ans;
        for (int i = 0; i < n && ans.size() < k; i++) {
            if (seg[i].a <= left && right <= seg[i].b) {
                ans.push_back(seg[i].id);
            }
        }
        for (int x : ans) {
            printf("%d ", x + 1);
        }
        puts("");
    }
}
