#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, M, Y;
    scanf("%d%d%d", &n, &M, &Y);

    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x[i]);
    }

    vector<int> k(n);
    int rem = 0;
    for (int i = 0; i < n; ++i) {
        k[i] = (x[i] * M) / Y;
        rem += k[i];
    }
    rem = M - rem;
    vector<int> indices(n);
    for (int i = 0; i < n; ++i) indices[i] = i;
    sort(indices.begin(), indices.end(),
            [&](int a, int b) {
                return Y * k[a] - M * x[a] <
                       Y * k[b] - M * x[b];
            });
    for (int i = 0; i < rem; ++i) {
        ++k[indices[i]];
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", k[i]);
    }
    puts("");
}
