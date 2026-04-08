
#include <stdio.h>

void foo(int **pInt) {
  printf("%p\n", *pInt);
  printf("%d\n", **pInt);
}

int main() {
  int i = 10;
  int *p = &i;

  foo(&p);
}
