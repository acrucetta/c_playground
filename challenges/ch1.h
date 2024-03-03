#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void merge(double *arr, int left, int middle, int right);
void merge_sort(double *arr, int left, int right);
bool is_array_sorted(double *arr, int length);
void swap(double *a, double *b);
int partition(double *arr, int low, int high);
void quick_sort(double *arr, int low, int high);
