// Author: Ivan Kazmenko aka Gassa, gassa@mail.ru

#include <stdio.h>

int cur_space, space, start_file, start_line, eoln, num_10, num_13;
int multi_eoln, multi_eoln_end;

void new_line (void)
{
 putchar ('\n');
 start_line = 1;
}

int main (void)
{
 int c, i;
 start_file = 1;
 start_line = 1;
 space = 0;
 eoln = 0;
 num_10 = 0;
 num_13 = 0;
 multi_eoln = 0;
 multi_eoln_end = 0;

 while ((c = getchar ()) != EOF)
 {
  // update state
  cur_space = (c == 9 || c == 10 || c == 13 || c == 32);
  if (cur_space)
   space = 1;
  if (c == 10 || c == 13)
   eoln = 1;
  num_10 += (c == 10);
  num_13 += (c == 13);

  // output non-whitespace characters
  if (!cur_space)
  {
   if (eoln)
   {
    for (i = 0; i < num_10 || i < num_13; i++)
     new_line ();
    if (start_file + i > 1)
     multi_eoln = 1;
   }
   if (!start_line && space)
    putchar (' ');
   putchar (c);
   start_file = 0;
   start_line = 0;
   space = 0;
   eoln = 0;
   num_10 = 0;
   num_13 = 0;
  }
 }

 // insert at least one end-of-line before end-of-file if it is not empty
 if (!start_file && !eoln)
  num_10 = num_13 = 1;

 for (i = 0; i < num_10 || i < num_13; i++)
  new_line ();
 if (start_file + i > 1)
  multi_eoln_end = 1;

 if (multi_eoln)
  fprintf (stderr, "Warning: empty lines in file\n");
 if (multi_eoln_end)
  fprintf (stderr, "Warning: empty lines at end of file\n");
 return 0;
}
