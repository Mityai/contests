#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <cstdio>
#define fi first
#define se second
using namespace std;

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int N, R, O, Y, G, B, V;
        scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);

        vector<pair<int, char>> C = {{R, 'R'}, {Y, 'Y'}, {B, 'B'}};
        sort(C.begin(), C.end());
        string S;
        S += C[0].se;
        S += C[1].se;
        S += C[2].se;
        vector<int> A = {C[0].fi, C[1].fi, C[2].fi};
        int mn = A[0];
        list<char> q;
        for (int i = 0; i < 3 * mn; ++i) {
            q.push_back(S[i % 3]);
        }
        A[0] -= mn;
        A[1] -= mn;
        A[2] -= mn;
        int mn2 = min(A[1], A[2]);
        for (int i = 0; i < 2 * mn2; ++i) {
            q.push_back(S[i % 2 + 1]);
        }
        A[1] -= mn2;
        A[2] -= mn2;
        int left = A[2];
        printf("Case #%d: ", test);
        if (left <= mn) {
            auto it = q.begin();
            ++it;
            for (int i = 1; i <= left; ++i) {
                it = q.insert(it, S[2]);
                ++it;
                ++it;
                ++it;
            }
            for (char x : q) {
                printf("%c", x);
            }
            puts("");
        } else {
            puts("IMPOSSIBLE");
        }
    }
}
