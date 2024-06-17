
#include <stdio.h>
struct tag {
  char lname[20];
  char fname[20];
  int age;
  float rate;
};

struct tag my_struct;

int main() {
  char a[20];
  int i;

  a[3] = 'x';
  3 [a] = 'y';

  printf("%c", a[3]);

  return 0;
}
