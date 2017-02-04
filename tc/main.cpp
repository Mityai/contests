#include <bits/stdc++.h>
using namespace std;

int norm(vector <int> S, int P) {
    sort(S.begin(), S.end());

    int n = (int)S.size();
    int dp[n][P + 1];
    memset(dp, 127, sizeof dp);
    const int INF = dp[0][0];

    for (int i = 0; i < n; i++) {
        dp[i][0] = 0;
    }

    for (int i = 1; i < n; i++) {
        if (i == 1) {
            dp[i][1] = S[i] - S[i - 1];
        } else {
            for (int j = 0; j <= P; j++) {
                if (j + 1 <= P && dp[i - 2][j] != INF) {
                    dp[i][j + 1] = min(dp[i][j + 1], max(dp[i - 2][j], S[i] - S[i - 1]));
                }
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[i][P]);
    }
    
    return ans;
}

const int INF = 1e9 + 100;

int bad(vector<int> s, int p) {
    sort(s.begin(), s.end());

    vector<vector<int> > dp(s.size() + 1, vector<int> (p + 1, INF));
    dp[0][0] = 0;
    for (int i = 0; i <= s.size(); i++) {
        for (int j = 0; j <= p; j++) {
            if (i > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            }
            if (i > 1 && j > 0) {
                dp[i][j] = min(dp[i][j], max(dp[i - 2][j - 1], s[i - 1] - s[i - 2]));
            }
        }
    }
    return dp[s.size()][p];
}

const int N = 10;
const int C = 100;

int main() {
    srand(time(NULL));
    while (true) {
        int n = rand() % (N - 1) + 2;
        vector<int> S(n);
        for (int i = 0; i < n; i++) {
            S[i] = rand() % C + 1;
        }
        int P = rand() % (n / 2) + 1;
        assert(1 <= P && P <= n / 2);

        if (norm(S, P) != bad(S, P)) {
            printf("%d\n", n);
            for (int x : S) {
                printf("%d ", x);
            }
            puts("");
            printf("%d\n", P);
            printf("norm = %d bad = %d\n", norm(S, P), bad(S, P));
            return 0;
        }
    }
}
