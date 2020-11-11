#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

struct queue {
   double *items;
   int head;
   int capacity;
   int num_items;
};

queue queue_new() {
   int default_size = 7;
   queue q = emalloc(sizeof *q);
   q->head = 0;
   q->capacity = default_size;
   q->num_items = 0;
   q->items = emalloc(q->capacity * sizeof q->items[0]);
   return q;
}

void enqueue(queue q, double item) {
   if (q->num_items < q->capacity) {
      q->items[(q->head + q->num_items) % q->capacity] = item;
      q->num_items++;
   }
}

double dequeue(queue q) {
   int rm = 0;
   rm = q->head;
   if (q->num_items > 0) {
      q->num_items--;
      q->head++;
      return q->items[rm];
   } else {
      return EXIT_FAILURE;
   }
}

void queue_print(queue q) {
   /* print queue contents one per line to 2 decimal places */
   int i = 0;
   if (q->num_items != 0) {
      while (i < q->num_items) {
         printf("%.2f\n", q->items[i]);
         i++;
      }
   }
}

void queue_print_info(queue q) {
   int i;
   printf("capacity %d, num_items %d, head %d\n[", q->capacity,
         q->num_items, q->head);
   for (i = 0; i < q->capacity; i++) {
      printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
   }
   printf("]\n");
}

int queue_size(queue q) {
   if (q->num_items != 0) {
        return q->num_items;
    }else {
        return 0;
    }
}

queue queue_free(queue q) {
   free(q->items);
   free(q);
   return q;
}
