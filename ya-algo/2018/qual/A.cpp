#include <bits/stdc++.h>
using namespace std;

const int N = 32;

bool ok(const vector<int>& tickets, const vector<char>& good) {
    int cnt = 0;
    for (int x : tickets) {
        cnt += good[x];
    }
    return cnt >= 3;
}

int main() {
    vector<char> good(N);

    for (int i = 0; i < 10; ++i) {
        int x;
        scanf("%d", &x);
        good[x - 1] = true;
    }

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        vector<int> ticket(6);
        for (int j = 0; j < ticket.size(); ++j) {
            scanf("%d", &ticket[j]);
            --ticket[j];
        }
        if (ok(ticket, good)) {
            puts("Lucky");
        } else {
            puts("Unlucky");
        }
    }
}
