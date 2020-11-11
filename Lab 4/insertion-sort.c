#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Sets the size of the array */
#define ARRAY_MAX 30000

/* Insertion sort algorithm */
void insertion_sort(int *a, int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            j = j - 1;
        }
        a[j+1] = key;
    }
}

int main(void) {
    /* Variable Declarations */
    int my_array[ARRAY_MAX]; /* Will store the input numbers and the end sorted numbers */
    clock_t start, end; /* Used to time the insertion sort */
    int i, count = 0; /* Counters */

    /* Gets input from the terminal */
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    /* Run the insertion sort and time it */
    start = clock();
    insertion_sort(my_array, count);
    end = clock();

    /* Print out the final sorted array */
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    /* Timing information (number of items and time taken) */
    fprintf(stderr, "%d %f\n", count, (end - start)/ (double) CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}
