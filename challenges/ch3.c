#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// CHALLENGE 3(π).Compute the N first decimal places of π ?

double compute_pi(int iters) {
  double pi = 0;
  for (int i = 0; i <= iters; i++) {
    double iter_value = log10((pow(640320, 3) / (24 * 6 * 2 * 6)));
    pi += iter_value;
  }
  return pi;
}

int main() {
  double pi;
  pi = compute_pi(5);
  printf("%f", pi);
  return 0;
}
