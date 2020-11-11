#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct int_queue_item *int_queue_item;

struct int_queue_item {
	int item;
	int_queue_item next;
};

struct int_queue_record {
	int_queue_item first;
	int_queue_item last;
	int length;
};

int int_dequeue(int_queue q) {
	int_queue_item head = q->first;
	int output;
	if (NULL == head) return 0.0;
	q->first = q->first->next;
	output = head->item;
	free(head);
	q->length--;
	return output;
}

int int_queue_size(int_queue q) {
	return q->length;
}

int_queue int_queue_new() {
	int_queue q = emalloc(sizeof *q);
	q->first = NULL;
	q->last = NULL;
	q->length = 0;
	return q;
}

void int_enqueue(int_queue q, int item) {
	int_queue_item new_int_queue_item = NULL;
	if (NULL == q->first) {
		q->first = emalloc(sizeof *new_int_queue_item);
		q->first->item = item;
		q->first->next = NULL;
		q->last = q->first;
		q->length++;
	} else {
		new_int_queue_item = emalloc(sizeof *new_int_queue_item);
		new_int_queue_item->item = item;
		new_int_queue_item->next = NULL;
		q->last->next = new_int_queue_item;
		q->last = new_int_queue_item;
		q->length++;
	}
}

void int_queue_free(int_queue q) {
	while (q->length > 0) int_dequeue(q);
	free(q);
}

void int_dequeue_print(int_queue q) {
	int_queue_item iter;
	for (iter = q->first; NULL != iter; iter = iter->next) {
		printf("%d\n", iter->item);
	}
}
