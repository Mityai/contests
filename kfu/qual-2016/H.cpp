#include <bits/stdc++.h>
using namespace std;

int f[6][6][6][6];

bool ask(int a1, int b1, int a2, int b2) {
    if (f[a1][b1][a2][b2]) {
        return f[a1][b1][a2][b2] - 1;
    }
    printf("? %d %d %d %d\n", a1 + 1, b1 + 1, a2 + 1, b2 + 1);
    fflush(stdout);
    string ret;
    cin >> ret;
    f[a1][b1][a2][b2] = (ret != "YES") + 1;
    return f[a1][b1][a2][b2] - 1;
}

void ans(int a1, int b1, int a2, int b2, int a3, int b3) {
    printf("! %d %d %d %d %d %d\n", a1 + 1, b1 + 1, a2 + 1, b2 + 1, a3 + 1, b3 + 1);
    fflush(stdout);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int a1 = 0; a1 < 6; a1++) {
        for (int b1 = a1 + 1; b1 < 6; b1++) {
            for (int a2 = a1 + 1; a2 < 6; a2++) {
                for (int b2 = a2 + 1; b2 < 6; b2++) {
                    for (int a3 = a2 + 1; a3 < 6; a3++) {
                        for (int b3 = a3 + 1; b3 < 6; b3++) {
                            set<int> q;
                            q.insert(a1);
                            q.insert(a2);
                            q.insert(a3);
                            q.insert(b1);
                            q.insert(b2);
                            q.insert(b3);
                            if (q.size() == 6) {
                                if (ask(a1, b1, a2, b2) && ask(a1, b1, a3, b3) && ask(a2, b2, a3, b3)) {
                                    ans(a1, b1, a2, b2, a3, b3);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
