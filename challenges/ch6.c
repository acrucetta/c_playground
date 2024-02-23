// CHALLENGE 6 (linear algebra). Some of the most important problems for which
// arrays are used stem from linear algebra.
//
// Can you write functions that do vector-to-vector or matrix-to-vector products
// at this point?
//
// What about Gauß elimination or iterative algorithms for matrix inversion?

#include <stdlib.h>

// e.g., [1,2] * [1,2] = a1b1 + a2b2 = 5
int dot_product(int *v1, int *v2) { return EXIT_SUCCESS; }

// e.g., [1,2] * [1,2] = [1,4]
int element_wise_product(int *v1, int *v2) { return EXIT_SUCCESS; }

int gaus_elimination(int *m1) { return EXIT_SUCCESS; }

int invert_matrix(int *m1) { return EXIT_SUCCESS; }

int main() {
  double v1[] = {1, 2, 3};
  double v2[] = {1, 2, 3};
  double result[];

  result = dot_product(v1, v2);

  return EXIT_SUCCESS;
}
