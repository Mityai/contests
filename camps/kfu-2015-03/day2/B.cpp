#include <bits/stdc++.h>
using namespace std;

struct F {
    int O, V, N;
};

int main() {
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1) {
        vector<F> f(n);
        for (int i = 0; i < n; i++) {
            scanf("%d-%d-%d", &f[i].O, &f[i].V, &f[i].N);
        }

        int O = 0, V = 0, N = 0, OV = 0, VN = 0, ON = 0, OVN = 0;

        int m;
        scanf("%d", &m);

        for (int i = 0; i < m; i++) {
            string s;
            cin >> s;

            sort(s.begin(), s.end());
            if (s == "O") O++;
            if (s == "V") V++;
            if (s == "N") N++;
            if (s == "NO") ON++;
            if (s == "OV") OV++;
            if (s == "NV") VN++;
            if (s == "NOV") OVN++;
        }

        for (int i = 0; i < n; i++) {
            auto q = f[i];
            q.O = max(q.O - O, 0);
            q.V = max(q.V - V, 0);
            q.N = max(q.N - N, 0);
            bool ok = false;
            for (int ov = 0; ov < 2 && !ok; ov++) {
                auto q1 = q;
                if (ov == 0) {
                    int d = min(q1.O, OV);
                    q1.O -= d;
                    OV -= d;
                    q1.V = max(0, q1.V - OV);
                    OV += d;
                }
                if (ov == 1) {
                    int d = min(q1.V, OV);
                    q1.V -= d;
                    OV -= d;
                    q1.O = max(0, q1.O - OV);
                    OV += d;
                }
                for (int vn = 0; vn < 2 && !ok; vn++) {
                    auto q2 = q1;
                    if (vn == 0) {
                        int d = min(q2.V, VN);
                        q2.V -= d;
                        VN -= d;
                        q2.N = max(0, q2.N - VN);
                        VN += d;
                    }
                    if (vn == 1) {
                        int d = min(q2.N, VN);
                        q2.N -= d;
                        VN -= d;
                        q2.V = max(0, q2.V - VN);
                        VN += d;
                    }
                    for (int on = 0; on < 2 && !ok; on++) {
                        auto q3 = q2;
                        if (on == 0) {
                            int d = min(q3.O, ON);
                            q3.O -= d;
                            ON -= d;
                            q3.N = max(0, q3.N - ON);
                            ON += d;
                        }
                        if (on == 1) {
                            int d = min(q3.N, ON);
                            q3.N -= d;
                            ON -= d;
                            q3.O = max(0, q3.O - ON);
                            ON += d;
                        }
                        int cnt = q3.O + q3.V + q3.N;
                        if (cnt <= OVN) {
                            ok = true;
                        }
                    }
                }
            }
            if (ok) puts("DA");
            else puts("NE");
        }
    }
}
