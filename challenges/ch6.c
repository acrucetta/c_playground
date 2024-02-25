// CHALLENGE 6 (linear algebra). Some of the most important problems for which
// arrays are used stem from linear algebra.
//
// Can you write functions that do vector-to-vector or matrix-to-vector products
// at this point?
//
// What about Gauß elimination or iterative algorithms for matrix inversion?

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_M 4
#define SIZE_N 3

// e.g., [1,2] * [1,2] = a1b1 + a2b2 = 5
int dot_product(int *v1, int *v2, size_t length) {
  int result = 0;
  for (size_t i = 0; i < length; i++) {
    int element_prod = v1[i] * v2[i];
    result += element_prod;
  }
  return result;
}

// e.g., [1,2] * [1,2] = [1,4]
// We want to return a new array instead of doing it
// in place.
int *element_wise_product(int *v1, int *v2, size_t length) {
  int *result = malloc(length * sizeof(int));
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; i < length; i++) {
    result[i] = v1[i] * v2[i];
  }
  return result;
}

// Gauss Elimination
//
// The matrix A can be a 3x3 kmatrix while
// the matrix B is a 1D vector.
//
// We will need to make A into an upper triangular matrix
// and then use the solved rows to get the hidden variables.
int gauss_elimination(size_t M, size_t N, int A[static M][N]) {
  // Forward elimination
  for (int col = 0; col < N; col++) {
    // Make the diagonal element 1 and eliminate the column entry below it
    for (int row = col + 1; row < N; row++) {
      if (A[col][row] == 0) {
        return NULL;
      }
      int factor = A[row][col] / A[col][row];
    }
  }

  // Backward substitution

  return EXIT_SUCCESS;
}

int invert_matrix(int *m1) { return EXIT_SUCCESS; }

int main() {
  int v1[SIZE_N] = {1, 2, 3};
  int v2[SIZE_N] = {1, 2, 3};
  size_t length = sizeof(v1) / sizeof(v1[0]);

  int dot_result;
  dot_result = dot_product(v1, v2, length);
  assert(dot_result == 14);
  int *element_result = element_wise_product(v1, v2, length);
  size_t element_length = sizeof(element_result) / sizeof(element_result[0]);
  printf("%d", element_length);
  for (int i = 0; i <= element_length; i++) {
    printf("%i", element_result[i]);
  }

  int a[SIZE_M][SIZE_N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
  int b[SIZE_M] = {0};

  gauss_elimination(SIZE_M, SIZE_N, a);

  free(element_result);
  return EXIT_SUCCESS;
}
