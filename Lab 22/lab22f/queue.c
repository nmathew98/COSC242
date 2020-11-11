#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "mylib.h"

struct queue{
    double *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new(int size){
    int i;
    queue result = emalloc(sizeof *result);
    
    result->head = 0;
    result->capacity = size;
    result->num_items = 0;

    result->items = emalloc(result->capacity * sizeof result->items[0]);

    for(i = 0; i < result->capacity; i++){
        result->items[i] = 0;
    }
    return result;
}


void enqueue(queue q, double item){
    if(q->num_items < q->capacity){
        
        q->items[(q->head + q->num_items) % q->capacity] = item;
        q->num_items++;
    }
}


double dequeue(queue q){
    double temp;
    
    if(q->num_items > 0){
        temp = q->items[q->head];
        
        q->num_items--;
        q->head++;
        
        if(q->head == q->capacity -1){
            q->head = 0;
        }
        return temp;
    }else{
        return -999;
    }
}


void queue_print(queue q){
    int i;
    int items_to_print = q->num_items;
    
    for(i = q->head; i < items_to_print; i++){
        fprintf(stdout, "%f\n", q->items[i]);

        if(i > q->capacity -1){
            i = 0;
        }
    }
}


int queue_size(queue q){
    return q->num_items;
}


queue queue_free(queue q){
    if(NULL != q){
        free(q->items);
        free(q);
    }
    return q;
}
