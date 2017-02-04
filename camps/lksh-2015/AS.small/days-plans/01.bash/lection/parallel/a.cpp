#include <cstdio>
#include <windows.h>

int main() {
  int n = 0;
  while (n < 10) {
    printf("%d\n", ++n);
    fflush(stdout);
    Sleep(1000);
  }
}
