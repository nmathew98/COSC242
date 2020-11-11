#include <stdio.h>
#include <stdlib.h>

void display_repeats(int *a, int n) {
    int *b = malloc(sizeof a[0]);
    int i = 0;

    for (i = 0; i < n; i++) {
        b[a[i]]++;
    }

    printf("Number of times there were repeats: \nValue\t\t");
    for (i = 0; i < n; i++) {
        printf("%d\t", i);
    }
    printf("\nOccurance\t");
    for (i = 0; i < n; i++) {
        printf("%d\t", b[i]);
    }
    printf("\n");
    free(b);
}

int main(void) {
    int array_size = 0;
    int *my_dynamic_array;
    int i = 0;

    printf("Enter the size of the array: ");
    scanf("%d", &array_size);

    /* initialize the array to the appropriate size */
    my_dynamic_array = malloc(array_size * sizeof my_dynamic_array[0]);
    if (NULL == my_dynamic_array) {
        fprintf(stderr, "memory allocation failure!\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i++) {
        my_dynamic_array[i] = rand() % array_size;
    }
    printf("What's in the array:\n");
    for (i = 0; i < array_size; i++) {
        printf("%d ", my_dynamic_array[i]);
    }

    printf("\n");

    display_repeats(my_dynamic_array, array_size);
    /* release the memory associated with the array */
    free(my_dynamic_array);

    return EXIT_SUCCESS;
}
