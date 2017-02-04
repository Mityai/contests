#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int n;
  ll x;
  scanf("%d%lld", &n, &x);

  int sad = 0;
  for (int i = 0; i < n; i++) {
    char c;
    int d;
    scanf(" %c%d", &c, &d);
    if (c == '+') x += d;
    else if (x < d) sad++;
    else x -= d;
  }

  printf("%lld %d\n", x, sad);
}
