#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
	int capacity;
	int num_keys;
	char **keys;
};

static unsigned int htable_word_to_int(char *word) {
	unsigned int result = 0;
	while(*word != '\0') {
		result = (*word++ + 31 * result);
	}
	return result;
}


htable htable_new(int capacity) { 
	int i;
	htable h = emalloc(sizeof h);
	h->capacity = capacity;
	h->num_keys = 0;
	h->keys = emalloc(h->capacity * sizeof h->keys[0]);

	for (i = 0; i < capacity; i++) {
		h->keys[i] = NULL;
	}
	return h;
}


void htable_free(htable h) {
	int i;

	for (i = 0; i < h->capacity; i++) {
		if (h->keys[i] == NULL) free(h->keys[i]);
	}

	free(h);
}

int htable_insert(htable h, char *key) { 
	unsigned int str_to_int = htable_word_to_int(key);
	unsigned int index = str_to_int % h->capacity;
	unsigned int i = index;

	if (h->keys[index] == NULL) {
		h->keys[index] = emalloc((strlen(key) + 1) * sizeof(char));
		strcpy(h->keys[index], key);
		h->num_keys++;
	} else if (h->keys[index] != NULL) {
		do {
			i = (i + 1) % h->capacity;
			if (h->keys[i] == NULL) {
				h->keys[i] = emalloc((strlen(key) + 1) * sizeof(char));
				strcpy(h->keys[i], key);
				h->num_keys++;
				return 1;
			}
		} while (i != index);
		return 0;
	}
	return 0;
}

void htable_print(htable h, FILE *stream) {
	int i;
	for (i = 0; i < h->capacity; i++) {
		fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
	}
}
