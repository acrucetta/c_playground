// We want to sort double arrays
// with recursion. Using first
// merge sort then quick sort.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void merge(double *arr, int left, int middle, int right);
void merge_sort(double *arr, int left, int right);
bool is_array_sorted(double *arr, int length);
void swap(double *a, double *b);
int partition(double *arr, int low, int high);
void quick_sort(double *arr, int low, int high);

int main() {

  // Declare array
  double arr[] = {2, 3, 4, 1, 5, 100, 20};
  size_t arr_length = sizeof(arr) / sizeof(arr[0]);

  // Print the array
  for (int i = 0; i < arr_length; i++) {
    printf("\ni=%d - %f", i, arr[i]);
  }

  // Sort with merge sort
  merge_sort(arr, 0, arr_length);

  // Print the array
  printf("\nSorted Array:\n");
  for (int i = 0; i < arr_length; i++) {
    printf("\ni=%d - %f", i, arr[i]);
  }

  if (is_array_sorted(arr, arr_length)) {
    printf("Merge sort works!");
  };

  double arr2[] = {2, 3, 4, 1, 5, 100, 20};
  size_t arr2_length = sizeof(arr2) / sizeof(arr2[0]);
  quick_sort(arr2, 0, arr2_length - 1);
  if (is_array_sorted(arr2, arr2_length)) {
    printf("Merge sort works!");
    return EXIT_SUCCESS;
  };
  return EXIT_FAILURE;
}

bool is_array_sorted(double *arr, int length) {
  for (int i = 0; i < length - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }
  return true;
}

void merge(double *arr, int left, int middle, int right) {

  // Merge the two lists while they still have elements
  // We compare the smallest element of each half
  // and add them to the joint array
  int n1 = middle - left + 1;
  int n2 = right - middle;
  double left_list[n1], right_list[n2];

  // Creating temporary arrays
  for (int i = 0; i < n1; i++) {
    left_list[i] = arr[left + i];
  };
  for (int j = 0; j < n2; j++) {
    right_list[j] = arr[middle + 1 + j];
  };

  // Comparing each element in the arrays and adding them
  // to arr
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (left_list[i] <= right_list[j]) {
      arr[k] = left_list[i];
      i++;
    } else {
      arr[k] = right_list[j];
      j++;
    }
    k++;
  }

  // If there are any remaining elements copy them over
  while (i < n1) {
    arr[k] = left_list[i];
    i++;
    k++;
  }
  while (j < n2) {
    arr[k] = right_list[j];
    j++;
    k++;
  }
}

void merge_sort(double *arr, int left, int right) {
  // Merge sort splits an array recursively
  // It then compares the elements inside of it
  // and returns the sorted array
  if (left < right) {
    int middle = left + (right - left) / 2;
    merge_sort(arr, left, middle);
    merge_sort(arr, middle + 1, right);
    merge(arr, left, middle, right);
  }
}

void swap(double *a, double *b) {
  double t = *a;
  *a = *b;
  *b = t;
}

void quick_sort(double *arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
  }
}

int partition(double *arr, int low, int high) {
  double pivot = arr[high];
  int j = (low - 1);
  for (int i = low; i < high; i++) {
    if (arr[i] < pivot) {
      j++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[j + 1], &arr[high]);
  return (j + 1);
}
