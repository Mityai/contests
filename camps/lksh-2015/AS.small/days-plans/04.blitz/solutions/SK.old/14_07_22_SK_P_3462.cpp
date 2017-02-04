/**          
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int x[4], y[4];

int in( int xx, int yy )
{
  return x[2] <= xx && xx <= x[3] &&
         y[2] <= yy && yy <= y[3];
}

void out( int y1, int y2 )
{
  int lx = x[0], rx = x[1];
  if (!(y[3] <= y1 || y2 <= y[2]))
  {
    if (x[2] <= lx) lx = max(lx, x[3]);
    if (x[3] >= rx) rx = min(rx, x[2]);
  }
  printf("%d %d %d %d\n", lx, y1, rx, y2);
}

void outx( int x1, int x2 )
{
  int ly = y[0], ry = y[1];
  if (!(x[3] <= x1 || x2 <= x[2]))
  {
    if (y[2] <= ly) ly = max(ly, y[3]);
    if (y[3] >= ry) ry = min(ry, y[2]);
  }
  printf("%d %d %d %d\n", x1, ly, x2, ry);
}

int main()
{
  forn(i, 4)
    scanf("%d%d", &x[i], &y[i]);
  if (x[0] < x[2] && x[3] < x[1] &&
      y[0] < y[2] && y[3] < y[1])
  {
    printf("%d\n", 4);
    printf("%d %d %d %d\n", x[0], y[0], x[1], y[2]);
    printf("%d %d %d %d\n", x[0], y[2], x[2], y[3]);
    printf("%d %d %d %d\n", x[3], y[2], x[1], y[3]);
    printf("%d %d %d %d\n", x[0], y[3], x[1], y[1]);
    return 0;
  }
  
  if (x[2] <= x[0] && x[1] <= x[3] &&
      y[2] <= y[0] && y[1] <= y[3])
  {
    puts("0");
    return 0;
  }

  if (x[2] >= x[1] || x[3] <= x[0] ||
      y[2] >= y[1] || y[3] <= y[0])
  {
    printf("1\n");
    printf("%d %d %d %d\n", x[0], y[0], x[1], y[1]);
    return 0;
  }

  if (x[2] <= x[0] && x[1] <= x[3])
  {
    if (y[0] < y[2] && y[3] < y[1])
    {
      printf("2\n");
      printf("%d %d %d %d\n", x[0], y[0], x[1], y[2]);
      printf("%d %d %d %d\n", x[0], y[3], x[1], y[1]);
    }
    else
    {
      printf("1\n");
      printf("%d %d %d %d\n", x[0], max(y[0], y[2]), x[1], min(y[1], y[3]));
    }
    return 0;
  }

  if (y[2] <= y[0] && y[1] <= y[3])
  {
    if (x[0] < x[2] && x[3] < x[1])
    {
      printf("2\n");
      printf("%d %d %d %d\n", x[0], y[0], x[2], y[1]);
      printf("%d %d %d %d\n", x[3], y[0], x[1], y[1]);
    }
    else
    {
      printf("1\n");
      printf("%d %d %d %d\n", max(x[0], x[2]), y[0], min(x[1], x[3]), y[1]);
    }
    return 0;
  }

  if (in(x[0], y[0]) || in(x[0], y[1]) || in(x[1], y[0]) || in(x[1], y[1]))
  {
    printf("2\n");
    int ly = y[0];
    int my = (y[0] < y[2] && y[2] < y[1]) ? y[2] : y[3];
    int ry = y[1];
    out(ly, my);
    out(my, ry);
    return 0;
  }

  printf("3\n");
  if (y[0] <= y[2] && y[3] <= y[1])
  {
    out(y[0], y[2]);
    out(y[2], y[3]);
    out(y[3], y[1]);
  }
  else
  {
    outx(x[0], x[2]);
    outx(x[2], x[3]);
    outx(x[3], x[1]);
  }
  return 0;
}
                    