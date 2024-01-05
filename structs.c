#include <stdio.h>

struct car {
  char *name;
  int year;
  int hp;
  int price;
};

// Idiomatic way to set values
void set_price(struct car *c, int price) {
  c->price = price;
}

int main() {
  struct car c;
  c.name = "BMW";
  c.year = 2015;
  c.hp = 300;
  c.price = 50000;
  printf("Name: %s\n", c.name);
  printf("Year: %d\n", c.year);
  printf("HP: %d\n", c.hp);

  set_price(&c, 50);
  printf("Price: %d\n", c.price);
}
