/**
 * htable.c
 *
 * Includes create, insert, search and print functions for a hash table.
 * 
 * @author Naveen Mathew
 * @author Hugo Baird
 * @author Cedric Stephani
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

/**
 * Hash table structure.
 */
struct htablerec {
	int capacity; /* Hash table size */
	int num_keys; /* Number of keys in hash table */
	char **keys; /* Keys in hash table */
	int *frequencies; /* Frequency of occurence of each key */
	int *stats; /* Number of collisions for some number of keys */
	hashing_t method; /* Collision resolution strategy */
};

/**
 * Creates an instance of a hash table.
 *
 * @param capacity (int) states how many items the hash table can hold
 * @param method (hashing_t) states what collision resolution strategy to use
 * which can either be linear probing or double hashing
 * @return result the new hash table instance created
 */
htable htable_new(int capacity, hashing_t method) {
	int i = 0;

	/* Memory allocation */
	htable h = emalloc(sizeof * h);
	h->frequencies = emalloc(capacity * sizeof h->frequencies);
	h->stats = emalloc(capacity * sizeof h->stats);
	h->keys = emalloc(capacity * sizeof h->keys);

	/* Set default values */
	h->capacity = capacity;
	h->method = method;
	h->num_keys = 0;
	
	/* Initialize each element */
	for (i = 0; i < capacity; i++) {
		h->frequencies[i] = 0;
		h->stats[i] = 0;
		h->keys[i] = NULL;
	}

	return h;
}

/**
 * Inserts a word (string) into the hash table.
 *
 * @param h the hash table which is used to insert keys into
 * @param str the word to be inserted
 * @return 0 if the htable is full and frequency key occurs with if not
 */
int htable_insert(htable h, char *str) {
	unsigned int word_to_int = htable_word_to_int(str);
	unsigned int step = htable_step(h, word_to_int);
	int index = word_to_int % h->capacity;

	int collisions_counter = 0;

	for (;;) {
		/* If an index is found that is empty, copy str to index and 
		 * set the stats for the corresponding index to show how many
		 * collisions occured before we found the index. */
		if (h->keys[index] == NULL) {
			h->keys[index] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
			strcpy(h->keys[index], str);
			h->frequencies[index]++;
			h->stats[h->num_keys] = collisions_counter;
			h->num_keys++;
			return 1;

		/* If an index is found with the same string, icrement the frequency
		 * at that index. */
		} else if (strcmp(h->keys[index], str) == 0) {
			h->frequencies[index]++;
			return h->frequencies[index];
		}

		/* If we are using linear probing increment by 1, if not increment 
		 * by step */
		index += (h->method == LINEAR_P) ? 1 : step;
		index %= h->capacity;

		collisions_counter++;
		
		/* If there are many collisions as the capacity then there is no
		 * space left in the hash table */
		if (collisions_counter == h->capacity) return 0;
	}
}

/**
 * Searches through the hash table for specific words.
 *
 * @param h the hash table used to search for keys
 * @param str the word being searched for
 * @return 0 if word does not exist in hastable and frequency of key if not
 */
int htable_search(htable h, char *str) {
	int collisions = 0;
	
	unsigned int word_to_int = htable_word_to_int(str);
	unsigned int step = htable_step(h, word_to_int);
	int index = word_to_int % h->capacity;

	for (;;) {
		/* If the index found is empty, increment index and break out */
		if (h->keys[index] == NULL) {
			index++;
			break;
		}

		/* If the index found has the same str, increment the frequencies
		 * at that index */
		if (strcmp(h->keys[index], str) == 0) return h->frequencies[index];

		/* Increment index by 1 if the collision resolution strategy is
		 * linear probing, if not increase by step */
		index += (h->method == LINEAR_P) ? 1 : step;

		collisions++;
		index %= h->capacity;

		/* If there are as many collisions as the capacity of the hash
		 * table then the hash table is full */
		if (collisions == h->capacity) break;
	}
	return 0;
}

/**
 * Prints out the hash table.
 *
 * @param h the hash table to be printed out
 * @param print_info a function passed in to print frequencies and the word
 */
void htable_print(void (*print_info)(int freq, char *word_stdin), htable h) {
	int i = 0;

	for (i = 0; i < h->capacity; i++) {
		/* Print key if it is not null using print_info */
		if (h->keys[i] != NULL) (*print_info)(h->frequencies[i], h->keys[i]);
	}
}

/**
 * Prints the entire contents of the hash table.
 *
 * @param h the hash table to use to print out the entire contents
 */
void htable_print_entire_htable(htable h) {
	int i;

	fprintf(stderr, "  Pos  Freq  Stats  Word\n");
	fprintf(stderr, "----------------------------------------\n");
	for (i = 0; i < h->capacity; i++) {
		fprintf(stderr, "%5d %5d %5d   %s\n",
				i, h->frequencies[i], h->stats[i],
				h->keys[i] == NULL ? "" : h->keys[i]);
	}
}

/**
 * Prints out a table reflecting what certain attribute values were at during
 * regular intervals stated by num_stats whilst the hash table is created.
 *
 * @param h the hashtable to use to print the statistics from
 * @param stream the stream to print output to
 * @param num_stats the maximum number of snapshot statistics to print out
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
	int i;
	
	fprintf(stream, "\n%s\n\n",
			h->method == LINEAR_P ? "Linear Probing" : "Double Hashing");
	fprintf(stream, "Percent   Current    Percent    Average      Maximum\n");
	fprintf(stream, " Full     Entries    At Home   Collisions   Collisions\n");
	fprintf(stream, "------------------------------------------------------\n");
	for (i = 1; i <= num_stats; i++) {
		print_stats_line(h, stream, 100 * i / num_stats);
	}
	fprintf(stream, 
			"------------------------------------------------------\n\n");
}

/**
 * Frees up the memory allocated to the hash table.
 *
 * @param h the hash table to be freed from memory
 */
void htable_free(htable h) {
	int i;

	for (i = 0; i < h->capacity; i++) {
		if (h->keys[i] != NULL) free(h->keys[i]);
	}

	free(h->stats);
	free(h->keys);
	free(h->frequencies);
	free(h);
}

/**
 * Converts a word to an integer to use as an index position for searching.
 *
 * @param word a pointer to a word
 * @return result the word that is converted to an int
 */
unsigned int htable_word_to_int(char *word) {
	unsigned int result = 0;

	while (*word != '\0') {
		result = (*word++ + 31 * result);
	}

	return result;
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h the hash table
 * @param stream a stream to print the data to
 * @param percent_full the point at which to show the data from
 */
void print_stats_line(htable h, FILE *stream, int percent_full) {
	int current_entries = h->capacity * percent_full / 100;
	double average_collisions = 0.0;
	int at_home = 0;
	int max_collisions = 0;
	int i = 0;

	if (current_entries > 0 && current_entries <= h->num_keys) {
		for (i = 0; i < current_entries; i++) {
			if (h->stats[i] == 0) {
				at_home++;
			}
			if (h->stats[i] > max_collisions) {
				max_collisions = h->stats[i];
			}
			average_collisions += h->stats[i];
		}

		fprintf(stream, "%4d %10d %11.1f %10.2f %11d\n", percent_full,
				current_entries, at_home * 100.0 / current_entries,
				average_collisions / current_entries, max_collisions);
	}
}

/**
 * Calculates double hashing step to be applied to the key when a
 * collision occurs in the hash table.
 *
 * @param h the hash table the step is calculated for
 * @param i_key the index of the data the step is calculated for
 * @return the step value to increase the hash
 */
unsigned int htable_step(htable h, unsigned int i_key) {
	return 1 + (i_key % (h->capacity - 1));
}
