#include <bits/stdc++.h>
using namespace std;

using ll = long long;

unordered_map<int, ll> shift_nums, shift_trees;

int get_lvl(ll a) {
    int lvl = 0;
    while (a > 0) {
        a >>= 1;
        ++lvl;
    }
    return lvl - 1;
}

ll original_pos(ll x, int lvl) {
    return x - (1ll << lvl);
}

ll mod(ll x, int lvl) {
    ll cnt = 1ll << lvl;
    x %= cnt;
    if (x < 0) x += cnt;
    return x;
}

ll up(ll x, int lvl) {
    if (lvl == 0) return 0;
    ll pos = mod(original_pos(x, lvl) + shift_nums[lvl] + shift_trees[lvl], lvl);
    ll up_pos = mod(pos / 2 - shift_nums[lvl - 1] - shift_trees[lvl - 1], lvl - 1) + (1ll << (lvl - 1));
    return up_pos;
}

void print(ll x, int lvl) {
    while (lvl != -1) {
        printf("%lld ", x);
        x = up(x, lvl);
        --lvl;
    }
    putchar('\n');
}

int main() {
    int q;
    scanf("%d", &q);

    for (int j = 0; j < q; ++j) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            ll x, k;
            scanf("%lld%lld", &x, &k);
            shift_nums[get_lvl(x)] += k;
        } else if (t == 2) {
            ll x, k;
            scanf("%lld%lld", &x, &k);
            k %= 1ll << get_lvl(x);
            for (int i = get_lvl(x); i <= 61; ++i, k *= 2) {
                shift_trees[i] += k;
            }
        } else {
            ll x;
            scanf("%lld", &x);
            print(x, get_lvl(x));
        }
    }
}
