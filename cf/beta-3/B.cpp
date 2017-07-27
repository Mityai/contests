#include <bits/stdc++.h>
using namespace std;

struct Boat {
    int p, id;
};

bool cmp(const Boat& b1, const Boat& b2) {
    return b1.p > b2.p;
}

int main() {
    int n, v;
    scanf("%d%d", &n, &v);

    vector<Boat> kayak, catamaran;
    for (int i = 0; i < n; ++i) {
        int t, p;
        scanf("%d%d", &t, &p);
        if (t == 1) {
            kayak.push_back({p, i});
        } else {
            catamaran.push_back({p, i});
        }
    }

    sort(kayak.begin(), kayak.end(), cmp);
    sort(catamaran.begin(), catamaran.end(), cmp);

    vector<int> pk(kayak.size()), pc(catamaran.size());
    for (int i = 0; i < pk.size(); ++i) {
        pk[i] = kayak[i].p;
        if (i > 0) pk[i] += pk[i - 1];
    }
    for (int i = 0; i < pc.size(); ++i) {
        pc[i] = catamaran[i].p;
        if (i > 0) pc[i] += pc[i - 1];
    }

    int best_i = -1, best_j = -1, best_p = 0;
    for (int i = 0, vol = 2; i < catamaran.size() && v - vol >= 0; ++i, vol += 2) {
        int j = min(v - vol, int(kayak.size())) - 1;
        int cur_p = pc[i];
        if (j >= 0) cur_p += pk[j];
        if (best_p < cur_p) {
            best_p = cur_p;
            best_i = i;
            best_j = j;
        }
    }
    for (int i = 0; i < kayak.size() && i + 1 <= v; ++i) {
        if (best_p < pk[i]) {
            best_p = pk[i];
            best_i = -1;
            best_j = i;
        }
    }

    printf("%d\n", best_p);
    for (int i = 0; i <= best_i; ++i) printf("%d ", catamaran[i].id + 1);
    for (int i = 0; i <= best_j; ++i) printf("%d ", kayak[i].id + 1);
}
