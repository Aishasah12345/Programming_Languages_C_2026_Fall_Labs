
/*
 * week4_1_dynamic_array.c
 * Author: AISHA SAH
 * Student ID: 260AIB131
 * Description:
 *   Creates a dynamic integer array, calculates its sum
 *   and average, and frees allocated memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;
  int* arr = NULL;

  printf("Enter number of elements: ");

  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  arr = malloc((size_t)n * sizeof(int));

  if (arr == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);

  int sum = 0;

  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Invalid input.\n");
      free(arr);
      return 1;
    }

    sum += arr[i];
  }

  double average = (double)sum / n;

  printf("Sum = %d\n", sum);
  printf("Average = %.2f\n", average);

  free(arr);

  return 0;
}
