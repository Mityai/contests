/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#ifdef _WIN32
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

int main()
{
  int T, H, V;
  double A[4], B[4];
  scanf("%d%d%d", &T, &H, &V);

  A[0] = +1, B[0] = 0; // L
  A[1] = +1, B[1] = H; // R
  A[2] = -1, B[2] = (T + V - H) / 2.0; // U
  A[3] = -1, B[3] = (T - V - H) / 2.0; // D

  int M = (int)2e8;
  double L = -M, R = M;
  forn(i, 4)
    if (A[i] == -1)
    {
      R = min(R, B[i] + M);
      L = max(L, B[i] - M);
    }  
    else
    {
      R = min(R, -B[i] + M);
      L = max(L, -B[i] - M);
    }

  int x = (int)((L + R) / 2 + 1e-1);
  forn(i, 4)
    printf("%.0f\n", A[i] * x + B[i]);
  return 0;
}
