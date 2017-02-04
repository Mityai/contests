/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define IS(a, i) (((a) >> (i)) & 1)
#define S1(a, i) ((a) | (1 << (i)))
#define S0(a, i) ((a) & ~(1 << (i)))

typedef long long ll;

int w, h;
ll mem[2][1 << 16][1 << 4];
ll (*f0)[1 << 4] = mem[0];
ll (*f1)[1 << 4] = mem[1];

int main()
{
  scanf("%d%d", &w, &h);

  f0[0][0] = 1;
  forn(x, w)
    forn(y, h)
    {
      memset(f1, 0, sizeof(mem[0]));
      forn(pr, 1 << (h + 1))
        forn(type, 16)
        {
          ll F = f0[pr][type];
          if (!F)
            continue;
          //printf("%d,%d : %d, %d\n", x, y, pr, type);
          if (IS(pr, y + 1))
          {
            f1[S0(pr, y + 1)][type] += F;
          }
          else
          {
            if (y && !IS(pr, y - 1) && !IS(pr, y))
              f1[S1(S1(pr, y), y - 1)][type | 1] += F;
            if (y + 1 < h && !IS(pr, y + 2) && !IS(pr, y))
              f1[S1(S1(pr, y), y + 2)][type | 2] += F;
            if (y + 1 < h && !IS(pr, y))
              f1[S1(S1(pr, y), y + 1)][type | 4] += F;
            if (y + 1 < h && !IS(pr, y + 2))
              f1[S1(S1(pr, y + 2), y + 1)][type | 8] += F;
          }
        }
      swap(f0, f1);
      if (y == h - 1)
      {
        memset(f1, 0, sizeof(mem[0]));
        forn(pr, 1 << (h + 1))
          forn(type, 16)
            if (f0[pr][type])
            {
              //printf("[%d,%d]\n", pr, type);
              assert(!IS(pr, h));
              f1[pr << 1][type] += f0[pr][type];
            }
        swap(f0, f1);
      }
    }
  
  ll sum = 0;
  forn(j, 15)
    sum += f0[0][j];
  cout << sum << endl;
  return 0;
}
