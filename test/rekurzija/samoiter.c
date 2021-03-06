#include <stdio.h>

static int broj = 5;

void viter() {
  while (broj) {
    printf("%d", broj);
    broj--;
    continue;
  }
  putchar('\n');
}

int itenr(long a, int rez) {
  while (!(a <= 0)) {
    long a0 = a - 1;
    int rez0 = rez + 1;
    a = a0;
    rez = rez0;
    continue;
  }

  return rez;
}

// duboki polozaj poziva
int itenr2(long a, int rez) {
  while (!(a <= 0)) {
    rez--;
    {
      rez++;
      {
        {
          long a1 = a - 1;
          int rez1 = rez + 1;
          a = a1;
          rez = rez1;
          continue;
        }
      }
    }
  }
  {
    rez--;
    {
      rez++;
      { return rez; }
    }
  }
}

int itern(int a, int rez) {
  while (a > 0) {
    int a2 = a - 1;
    int rez2 = rez + 1;
    a = a2;
    rez = rez2;
    continue;
  }

  return rez;
}

// rekurzivni poziv u "bazi"
int itern2(int a, int rez) {
  if (a > 0)
    return itern2(a - 1, rez + 1);
  else {
    if (!a)
      return itern2(a - 1, rez);
    return rez;
  }
}

int ittnr(int a, int rez) {
  while (!(a <= 0)) {
    int a3 = a - 1;
    int rez3 = rez + 1;
    a = a3;
    rez = rez3;
    continue;
  }

  return rez;
}

// nerekurzivni poziv u bazi
int ittnr2(int a, int rez) {
  while (!(a <= 0)) {
    if (a > 5)
      return ittnr(a - 6, rez + 6);
    {
      int a4 = a - 1;
      int rez4 = rez + 1;
      a = a4;
      rez = rez4;
      continue;
    }
  }
  return rez;
}

int ittrn(int a, int rez) {
  while (a > 0) {
    int a5 = a - 1;
    int rez5 = rez + 1;
    a = a5;
    rez = rez5;
    continue;
  }

  return rez;
}

// return status istog tipa
int ittrn2(int a, int rez) {
  if (a > 0)
    return a;
  return rez;
}

void hello(int i) {
  while (i--)
    printf("hello\n");
}

void test1() {
  while (0)
    continue;

  ;
}

void test2() {
  while (!1)
    continue;

  ;
}

void test3() {
  if (1)
    ;
  else
    return test2();
}

void test4();

void test4() {
  if (0)
    ;
  return;
}

int main() {
  viter();
  printf("%d%d", itenr(1, 1), itenr2(2, 2));
  printf("%d%d\n", itern(3, 3), itern2(4, 4));

  int x = 3, y = x;
  while (x > 2) {
    y++;
    putchar(y + '0');
    break;
    putchar('x');
  }

  while (x > 2) {
    int z = 3;
    x = y - z;
    putchar(x + '0');
    continue;
    putchar('y');
  }

  // ugnezdjene petlje
  do
    while (1)
      break;
  while (0);

  // labela i goto
  for (; 1;)
  labela:
    break;

  while (0)
    goto labela;

  // rad sa funkcijama
  void (*f)(int) = &hello;
  while (x < 2) {
    f(x + 5);
    putchar('\n');
    hello(x + 3);
    break;
  }

  // petlja sa maskiranjem
  int k = 10;
  while (!k) {
    double k = 1;
    k--;

    while (0) {
      double k = 1;
      k--;
    }
  }

  printf("%d%d", ittrn(5, 0), ittrn2(6, 0));
  printf("%d%d\n", ittrn(7, 0), ittrn2(8, 0));

  test1();
  test2();
  test3();
  test4();

  return 0;
}
