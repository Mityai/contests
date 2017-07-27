#include <cstdio>
#include <cstring>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int max_len = (int)1e7;

FILE *F = NULL;
char s[max_len + 1];

void NewTest()
{
  int static cnt = 0;
  char buf[99];

  do
  {
    if (F)
      fclose(F);
    cnt++;
    sprintf(buf, "%02d.tmp", cnt);
    F = fopen(buf, "rt");
  } while (F);

  sprintf(buf, "%02d.tmp", cnt);
  F = fopen(buf, "wt");
}

int main()
{
  while (gets(s))
  {
    NewTest();
    do
      fprintf(F, "%s\n", s);
    while (gets(s) && strlen(s) > 0);
  }

  if (F)
    fclose(F);
  return 0;
}
