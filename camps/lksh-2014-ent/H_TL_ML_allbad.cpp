#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <map>
#define WITHFILES 1
#define PROBLEM "number"
#define ll long long
using namespace std;

string s, t, s0;
vector<string> a, b;
int was[10000000];
int ans = INT_MAX;

void rec(string st, int step) {
    int st_n;
    sscanf(st.c_str(), "%d", &st_n);
    if (st == t) {
        if (ans > step)
            ans = step;
        return;
    }

    if (step + 1 >= ans) {
        return;
    }

    was[st_n] = step;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < st.length() - 1; j++) {
            if (a[i][0] == st[j] && a[i][1] == st[j+1]) {
                s0 = st;
                s0[j] = b[i][0];
                s0[j+1] = b[i][1];
                int st0_n;
                sscanf(s0.c_str(), "%d", &st0_n);
                if (was[st0_n] == 0 || was[st0_n] > step + 1) {
                    rec(s0, step + 1);
                }
            }
        }
    }
}

int main() {
    #if __APPLE__ || !WITHFILES
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);
    #endif

    int L;
    scanf("%d", &L);
    cin >> s >> t;
    int K;
    scanf("%d", &K);
    a.resize(K); b.resize(K);   
    for (int i = 0; i < K; i++) {
        cin >> a[i] >> b[i];
    }
    rec(s, 0);
    if (ans == INT_MAX) {
        printf("-1");
    } else {
        printf("%d", ans);
    }
}