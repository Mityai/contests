#include <cstdio>
#include <algorithm>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int n = 10;
int a[n];

void out()
{
  printf("%d :", n);
  forn(i, n)
    printf(" %d", a[i]);
  puts("");
}

int main()
{
  forn(i, n)
    a[i] = i;
  out();
  std::rotate(a, a + n - 1, a + n);
  out();
  return 0;
}
  