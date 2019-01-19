#include <cstdio>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> a(int(1e5) + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        ++a[x];
    }

    for (int x : a) {
        if (x & 1) {
            puts("Conan");
            return 0;
        }
    }
    puts("Agasa");
}
