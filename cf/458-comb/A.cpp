#include <cstdio>
#include <algorithm>

bool is_square(int x) {
    static const int MAX = 1e3;

    if (x < 0) {
        return false;
    }
    for (int y = 0; y <= MAX; ++y) {
        if (y * y == x) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    scanf("%d", &n);

    bool was = false;
    int ans;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        if (!is_square(x)) {
            if (was) {
                ans = std::max(ans, x);
            } else {
                ans = x;
                was = true;
            }
        }
    }

    printf("%d\n", ans);
}
