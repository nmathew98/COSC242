#include <stdio.h>
#include <stdlib.h>

void random_repeats(int *n, int size) {
    int *counter = malloc(size * sizeof counter[0]);
    int i, j;
    
    if (NULL == counter) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (n[i] == j)
                counter[j]++;

    for (i = 0; i < size; i++)
        if (counter[i] > 1)
            printf("%d occurs %d times\n", i, counter[i]);

    free(counter);
}

int main(void) {
    int array_size = 0;
    int *my_array;
    int i = 0;

    printf("Enter the size of the array:\n");
    scanf("%d", &array_size);

    my_array = malloc(array_size * sizeof my_array[0]);
    if (NULL == my_array) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i++) {
        my_array[i] = rand() % array_size;
    }

    printf("What's in the array:\n");
    for (i = 0; i < array_size; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");
    random_repeats(my_array, array_size);
    free(my_array);
    return EXIT_SUCCESS;
}
    
