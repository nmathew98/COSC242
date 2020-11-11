#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"
    
struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t size) {
    void *result = malloc(size);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

void *erealloc(int *p, size_t size) {
    void *result = realloc(p, size);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

flexarray flexarray_new() {
    /* initialise flexarray structure (including items array) */
    int i;
    flexarray f = emalloc(sizeof *f);
    f->capacity = 2;
    f->itemcount = 0;
    f->items = emalloc(2 * sizeof f->items[0]);

    for (i = 0; i < f->capacity; i++)
        f->items[i] = 0;

    return f;
}
    
void flexarray_append(flexarray f, int num) {
    /* add an item to the flexarray, expanding as necessary */
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount] = num;
    f->itemcount++;
}
    
void flexarray_print(flexarray f, FILE *stream) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for (i = 0; i < f->itemcount; i++)
        fprintf(stream, "%d\n", f->items[i]);
}
    
void flexarray_sort(flexarray f) {
    /* sort into ascending order */
    int i, j, smallest_value, smallest_index, temp;

    for (i = 0; i < f->itemcount; i++) {
        smallest_value = f->items[i];
        smallest_index = i;

        if (i == f->itemcount / 2)
            flexarray_print(f, stderr);

        for (j = i + 1; j < f->itemcount; j++) {
            if (f->items[j] < smallest_value) {
                smallest_value = f->items[j];
                smallest_index = j;
            }
        }

        temp = f->items[i];
        f->items[i] = smallest_value;
        f->items[smallest_index] = temp;
    }
}
    
void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    free(f->items);
    free(f);
}
