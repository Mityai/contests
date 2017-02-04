#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool good(int x) {
    vector<int> d;
    while (x > 0) {
        d.push_back(x % 10);
        x /= 10;
    }
    reverse(d.begin(), d.end());

    bool ok1 = true;
    for (int i = 0; i < (int)d.size(); i++) {
        if (d[i] != 1 && d[i] != 3 && d[i] != 8 && d[i] != 0) ok1 = false;
    }
    
    bool ok2 = true;
    int n = (int)d.size();
    if (n % 2 == 1) {
        if (d[n / 2] != 0 && d[n / 2] != 8) ok2 = false;
    }
    for (int i = 0; i < n / 2; i++) {
        if (d[i] == 2 && d[n - i - 1] == 5) continue;
        if (d[i] == 5 && d[n - i - 1] == 2) continue;
        if (d[i] == 8 && d[n - i - 1] == 8) continue;
        if (d[i] == 0 && d[n - i - 1] == 0) continue;
        ok2 = false;
    }
    return ok1 | ok2;
}

const int MOD = 1e9 + 7;

void sub(ll &x, ll y) {
    x = (x - y) % MOD;
    if (x < 0) x += MOD;
}

void add(ll &x, ll y) {
    x = (x + y) % MOD;
}

void mult(ll &x, ll y) {
    x = (x * y) % MOD;
}

vector<int> h = {1, 3, 8, 0};
vector<int> v = {2, 5, 8, 0};

ll calc(int len) {
    if (len == 1) return 4;

    ll vert[len + 1][10], hor[len + 1][10];
    memset(vert, 0, sizeof vert);
    memset(hor, 0, sizeof hor);
    
    hor[1][1] = hor[1][3] = hor[1][8] = 1;
    for (int i = 2; i <= len; i++) {
        for (int dig : h) {
            for (int prevdig : h) {
                add(hor[i][dig], hor[i - 1][prevdig]);
            }
        }
    }

    vert[1][2] = vert[1][5] = vert[1][8] = 1;
    for (int i = 2; i <= len / 2; i++) {
        for (int dig : v) {
            for (int prevdig : v) {
                add(vert[i][dig], vert[i - 1][prevdig]);
            }
        }
    }
    ll ret = 0;
    for (int dig : v) {
        add(ret, vert[len / 2][dig]);
    }
    if (len % 2 == 1) {
        mult(ret, 2);
    }

    for (int dig : h) {
        add(ret, hor[len][dig]);
    }

    ll dp[len + 1][10];
    memset(dp, 0, sizeof dp);
    dp[1][8] = 1;
    for (int i = 2; i <= (len + 1) / 2; i++) {
        add(dp[i][0], dp[i - 1][8]);
        add(dp[i][0], dp[i - 1][0]);
        add(dp[i][8], dp[i - 1][8]);
        add(dp[i][8], dp[i - 1][0]);
    }
    
    sub(ret, dp[(len + 1) / 2][0]);
    sub(ret, dp[(len + 1) / 2][8]);
    //sub(ret, (1LL << ((len - 1) / 2)));
    return ret;                
}

ll solve(ll X) {
    if (X == -1) return 0;
    if (X == 0) return 1;
    vector<int> d;
    int len = 0;
    while (X > 0) {
        d.push_back(X % 10);
        X /= 10;
        len++;
    }
    d.push_back(0);
    reverse(d.begin(), d.end());

    if (len == 1) {
        if (d[1] == 0) return 1;
        if (d[1] < 3) return 2;
        if (d[1] < 8) return 3;
        if (d[1] <= 9) return 4;
    }

    ll ret = 0;
    for (int i = 1; i <= len - 1; i++) {
        add(ret, calc(i));
    }

    ll vert[len + 1][10][2], hor[len + 1][10][2];
    memset(vert, 0, sizeof vert);
    memset(hor, 0, sizeof hor);

    for (int dig : v) {
        if (dig == 0) continue;
        if (dig < d[1] && dig < d[len]) vert[1][dig][0] = 1;
        else if (dig == d[1] && dig == d[len]) vert[1][dig][1] = 1;
    }

    for (int i = 2; i <= len / 2; i++) {
        for (int dig : v) {
            for (int prevdig : v) {
                add(vert[i][dig][0], vert[i - 1][prevdig][0]);
                if (dig == d[i] && dig == d[len - i + 1]) add(vert[i][dig][1], vert[i - 1][prevdig][1]);
                if (dig < d[i] && dig < d[len - i + 1]) add(vert[i][dig][0], vert[i - 1][prevdig][0]);
            }
        }
    }
    ll cnt1 = 0;
    for (int dig : v) {
        add(cnt1, vert[len / 2][dig][0]);
    }
    if (len % 2 == 1) mult(cnt1, 2);

    ll cnt2 = 0;
    for (int dig : v) {
        add(cnt2, vert[len / 2][dig][1]);
    }
    if (len % 2 == 1 && 8 <= d[(len + 1) / 2]) mult(cnt2, 2);

    ll ansvert = 0;
    add(ansvert, cnt1);
    add(ansvert, cnt2);

    for (int dig : h) {
        if (dig == 0) continue;
        if (dig < d[1] && dig < d[len]) hor[1][dig][0] = 1;
        else if (dig == d[1] && dig == d[len]) hor[1][dig][1] = 1;
    }

    for (int i = 2; i <= len; i++) {
        for (int dig : h) {
            for (int prevdig : h) {
                add(hor[i][dig][0], hor[i - 1][prevdig][0]);
                if (dig == d[i] && dig == d[len - i + 1]) add(hor[i][dig][1], hor[i - 1][prevdig][1]);
                if (dig < d[i] && dig < d[len - i + 1]) add(hor[i][dig][0], hor[i - 1][prevdig][1]);
            }
        }
    }

    ll anshor = 0;
    for (int dig : h) {
        add(anshor, hor[len][dig][0]);
        add(anshor, hor[len][dig][1]);
    }

    ll dp[len + 1][10][2];
    memset(dp, 0, sizeof dp);
    if (8 < d[1] && 8 < d[len]) dp[1][8][0] = 1;
    else if (8 == d[1] && 8 == d[len]) dp[1][8][1] = 1;
    for (int i = 2; i <= (len + 1) / 2; i++) {
        add(dp[i][0][0], dp[i - 1][0][0]);
        add(dp[i][0][0], dp[i - 1][8][0]);
        add(dp[i][8][0], dp[i - 1][0][0]);
        add(dp[i][8][0], dp[i - 1][8][0]);
        if (0 == d[i] && 0 == d[len - i + 1]) add(dp[i][0][1], dp[i - 1][0][1]);
        if (0 == d[i] && 0 == d[len - i + 1]) add(dp[i][0][1], dp[i - 1][8][1]);
        if (8 == d[i] && 8 == d[len - i + 1]) add(dp[i][8][1], dp[i - 1][0][1]);
        if (8 == d[i] && 8 == d[len - i + 1]) add(dp[i][8][1], dp[i - 1][8][1]);
        if (0 < d[i] && 0 < d[len - i + 1]) add(dp[i][0][0], dp[i - 1][0][0]);
        if (0 < d[i] && 0 < d[len - i + 1]) add(dp[i][0][0], dp[i - 1][8][0]);
        if (8 < d[i] && 8 < d[len - i + 1]) add(dp[i][8][0], dp[i - 1][0][0]);
        if (8 < d[i] && 8 < d[len - i + 1]) add(dp[i][8][0], dp[i - 1][8][0]);
    }

    ll del = 0;
    add(del, dp[(len + 1) / 2][0][0]);
    add(del, dp[(len + 1) / 2][0][1]);
    add(del, dp[(len + 1) / 2][8][0]);
    add(del, dp[(len + 1) / 2][8][1]);

    /*
    printf("ret = %lld\n", ret);
    printf("vert = %lld\n", ansvert);
    printf("hor = %lld\n", anshor);
    printf("del = %lld\n", del);*/
    ll ans = 0;
    add(ans, ret);
    add(ans, ansvert);
    add(ans, anshor);
    sub(ans, del);
    return ans;
}

int main() {
#if __APPLE__
    //freopen("H.in", "r", stdin);
    //freopen("H.out", "w", stdout);
#endif

    ll a, b;
    while (cin >> a >> b) {
        ll ans = solve(b);
        sub(ans, solve(a - 1));
        cout << ans << endl;

        ll ans2 = 0;
        for (int i = a; i <= b; i++) {
            ans2 += good(i);
        }
        cout << ans2 << endl;
    }
}
