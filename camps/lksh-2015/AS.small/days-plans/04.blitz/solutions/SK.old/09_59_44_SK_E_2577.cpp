/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int MOD = (int)1e9 + 1;

int K, T, A, B;

int add( int a, int b ) { a += b; return a >= MOD ? a - MOD : a; }
int sub( int a, int b ) { a -= b; return a < 0 ? a + MOD : a; }
int mul( int a, int b ) { return ((ll)a * b) % MOD; }

int F( unsigned B )
{
  int res = 0;
  forn(i, K)
  {
    unsigned len = 1 << (i + 1);
    int num = (B >> (i + 1)) << i;
    unsigned x = B % len; len /= 2;
    if (x >= len)
      num += x - len;
    //printf("B = %d, i = %d, num = %d, %d\n", B, i, num, 1 << (K - i - 1));
    res = add(res, mul(num, 1 << (K - i - 1)));
  }
  //printf("res = %d\n", res);
  return res;        
}

int main()
{
  scanf("%d%d", &K, &T);
  while (T--)
  {
    scanf("%d%d", &A, &B);
    printf("%d\n", sub(F(B + 1), F(A)));
  }
  return 0;
}
