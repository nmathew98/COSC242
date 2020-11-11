#include <stdio.h>
#include <stdlib.h>

void max_min(int *a, int n, int *max, int *min) {
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] < *min) {
            *min = a[i];
        } else if (a[i] > *max) {
            *max = a[i];
        }
    }

    printf("Lowest value in array is: %d\n", *min);
    printf("Highest value in array is: %d\n", *max);
}

int main(void) {
    int some_array[] = { 1, 2, 3, 4, 5, 0 };
    int biggest, smallest;
    max_min(some_array, 6, &biggest, &smallest);

    return EXIT_SUCCESS;
}
