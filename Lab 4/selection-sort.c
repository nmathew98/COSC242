#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Sets the size of the array */
#define ARRAY_MAX 30000

/* Swaps the values of two variables */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* Selection sort algorithm */
void selection_sort(int *a, int n) {
    int i, j, min;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        swap(&a[min], &a[i]);
    }
}

int main(void) {
    /* Variable declarations */
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    /* Get input from the user */
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    /* Run the selection sort and time it */
    start = clock();
    selection_sort(my_array, count);
    end = clock();

    /* Prints out our final sorted array */
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    /* Prints out the number of items sorted and the timing information */
    fprintf(stderr, "%d %f\n", count, (end - start) / (double) CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
