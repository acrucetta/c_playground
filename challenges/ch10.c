// CHALLENGE 10 (Performance comparison of sorting algorithms). Can you compare
// the time efficiency of your sorting programs (challenge 1) with data sizes of
// several orders of magnitude? Be careful to check that you have some
// randomness in the creation of the data and that the data size does not exceed
// the available memory of your computer. For both algorithms, you should
// roughly observe a behavior that is proportional to N log N , where N is the
// number of elements that are sorted.
#include "ch1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void build_array(double *arr, size_t n) {
  /*Build array with random numbers of size N */
  int N = 1000;
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % N;
  }
}

int main() {

  // Declare the sorting array
  int arr_sizes[8] = {100, 1000, 10000, 100000, 1000000};
  for (int i = 0; i < 8; i++) {
    double *i_arr = (double *)malloc(arr_sizes[i] * sizeof(double));
    build_array(i_arr, arr_sizes[i]);
    clock_t start_time = clock();
    quick_sort(i_arr, 0, arr_sizes[i]);
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    // Print the result
    printf("Quick Sort: Time taken for array %d of size %d: %f seconds\n", i,
           arr_sizes[i], elapsed_time);

    double *i2_arr = (double *)malloc(arr_sizes[i] * sizeof(double));
    build_array(i2_arr, arr_sizes[i]);
    clock_t start_time2 = clock();
    merge_sort(i2_arr, 0, arr_sizes[i]);
    clock_t end_time2 = clock();
    double elapsed_time2 = (double)(end_time2 - start_time2) / CLOCKS_PER_SEC;
    // Print the result
    printf("Merge Sort: Time taken for array %d of size %d: %f seconds\n", i,
           arr_sizes[i], elapsed_time2);
  }
  return EXIT_SUCCESS;
}
