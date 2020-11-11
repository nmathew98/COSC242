#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

int main(void) {
    flexarray f = flexarray_new();
    int buffer;
    
    while (1 == scanf("%d", &buffer)) {
        flexarray_append(f, buffer);
    }

    flexarray_sort(f);
    flexarray_print(f, stdout);
    flexarray_free(f);

    return EXIT_SUCCESS;
}
