#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int H = 60;

bool who_win[H + 1][H + 1];
bool who[H + 1];

void pre_calc() {
    who[0] = who[1] = false;
    for (int i = 2; i <= H; ++i) {
        if (i % 2 == 0) {
            who[i] |= !who[i / 2];
        } else {
            who[i] = false;
        }
    }

    for (int last = 0; last <= H; ++last) {
        who_win[0][last] = false;
    }
    for (int cnt = 1; cnt <= H; ++cnt) {
        for (int last = 1; last <= H; ++last) {
            if (cnt != last) {
                who_win[cnt][last] = true;
            } else {
                who_win[cnt][last] = who[cnt];
            }
        }
    }
}
             
const int MAXN = 100000;
int f[MAXN];

int main() {
#if __APPLE__
    //freopen("E.in", "r", stdin);
    //freopen("E.out", "w", stdout);
#endif
    srand(time(NULL));

   int cur = 0;
	for (int i = 0; cur <= 60; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			f[cur++] = i;
		}
	}
    pre_calc();

    int n;
    for (int ww = 0; ww < 1000; ++ww) {
        n = rand() % 100;

        vector<int> a(n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            a[i] = rand() % 60 + 1;
            ans ^= a[i];
        }

        bool xorsum = 0;

        bool ok = false;
        for (int i = 0; i < n; ++i) {
            xorsum ^= 1;
            for (int j = 1; j <= a[i]; ++j) {
                xorsum ^= who_win[a[i] - j][j];
                if (xorsum == 0) {
                    ok = true;
                }
                xorsum ^= who_win[a[i] - j][j];
            }
            xorsum ^= 1;
        }

        ok = !ok;
        bool mak = (ans == 0);
        if (ok != mak) {
            puts("FAIL");
        }
    }
}
