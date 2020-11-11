#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct flexarrayrec *flexarray;

void *emalloc(size_t size);
void *erealloc(int *p, size_t size);

extern void        flexarray_append(flexarray f, int item);
extern void        flexarray_free(flexarray f);
extern flexarray   flexarray_new();
extern void        flexarray_print(flexarray f, FILE *stream);
extern void        flexarray_sort(flexarray f);
    
#endif
