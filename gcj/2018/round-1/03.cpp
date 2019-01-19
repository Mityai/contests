#include <bits/stdc++.h>
#define FILENAME "03"
using namespace std;

void solution() {
    int N;
    double P;
    scanf("%d%lf", &N, &P);

    double ans = 0;

    vector<pair<double, double>> a(N);
    for (int i = 0; i < N; ++i) {
        double H, W;
        scanf("%lf%lf", &H, &W);
        if (H > W) swap(H, W);
        double D = sqrt(H * H + W * W);
        a[i] = {2 * H, 2 * D};
        P -= 2 * (H + W);
        ans += 2 * (H + W);
    }

    sort(a.rbegin(), a.rend());
    for (int i = 0; i < N; ++i) {
        if (a[i].first > P) {
            continue;
        } else if (a[i].second <= P) {
            ans += a[i].second;
            P -= a[i].second;
        } else {
            ans += P;
            break;
        }
    }

    printf("%.10lf", ans);
}

void run_solution();

int main() {
#if __APPLE__
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
#endif

    run_solution();
}

void run_solution() {
    int T;
    scanf("%d", &T);

    for (int test = 1; test <= T; ++test) {
        printf("Case #%d: ", test);
        solution();
        putchar('\n');
    }
}
