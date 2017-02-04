#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  int steps = 0;
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    --x;
    steps = (steps + x) % 2;
    printf("%d\n", steps % 2 == 0 ? 2 : 1);
  }
}
