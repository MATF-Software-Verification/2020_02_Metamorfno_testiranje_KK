#include <stdio.h>

int main() {
  int x = 10;
  if (x--)
    do
      printf("%d", x);
    while (x--);

  if (x--)
    do {
      printf("%d", x);
      x += 2;
    } while (x--);

  putchar('\n');

  {
    {
      x = 10;
      if (x--)
        do {
          printf("%d", x);
          x--;
        } while (x--);
    }
  }

  if (1)
    do {
      x = 10;
      break;
    } while (1);

  printf("%d", x);
  putchar('\n');

  if (1)
    do {
      if (1)
        do
          break;
        while (1);

      x = 5;
      break;
    } while (1);

  printf("%d", x);
  putchar('\n');

  if (0)
    do {
    } while (0);

  if (0)
    do
      ;
    while (0);

  {
    x = -5;
    if (x)
      do {
        {
          x++;
          continue;
        }
        x++;
      } while (x);
  }

  {
    x = 0;
    if (x)
      do
        continue;
      while (x);
  }

  // ime je maskirano u staroj verziji
  int cond = 10;
  do
    cond--;
  while (cond > 5);

  // ime je maskirano u staroj verziji;
  // posledica je beskonacna petlja
  {
    int i = 0;
    if (i < 3)
      do {
        {
          double i0 = 3.1415926535897931;
          {
            i++;
            continue;
          }
        }
        i++;
      } while (i < 3);
  }

  return 0;
}
