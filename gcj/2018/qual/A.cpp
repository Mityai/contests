#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int T;
    scanf("%d", &T);
    
    for (int test = 1; test <= T; ++test) {
        int D;
        char S[31];
        scanf("%d %s", &D, S);
        int sz = strlen(S);
        
        ll sum_damage = 0;
        ll beam = 1;
        for (size_t i = 0; i < sz; ++i) {
            if (S[i] == 'C') {
                beam *= 2;
            } else {
                sum_damage += beam;
            }
        }
        
        int ans = 0;
        while (sum_damage > D) {
            bool ok = false;
            ll cur_beam = beam;
            for (int i = sz - 1; i >= 0; --i) {
                if (S[i] == 'C') cur_beam /= 2;
                if (S[i] == 'C' && (i + 1 < sz && S[i + 1] == 'S')) {
                    sum_damage -= cur_beam * 2;
                    sum_damage += cur_beam;
                    swap(S[i], S[i + 1]);
                    ++ans;
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                break;
            }
        }
        
        printf("Case #%d: ", test);
        if (sum_damage > D) {
            puts("IMPOSSIBLE");
        } else {
            printf("%d\n", ans);
        }
    }
}
