/**
 * mylib.c
 *
 * Includes helper functions for hash table application.
 *
 * @author Naveen Mathew
 * @author Hugo Baird
 * @author Cedric Stephani
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "mylib.h"

/**
 * emalloc function which allocates a block of memory.
 * 
 * @param s the size of memory needed to be allocated
 * @return a the memory address where the data has been allocated to
 */
void *emalloc(size_t s) {
	void *a = malloc(s);
	
	if (NULL == a) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	return a;
}

/**
 * getword function which reads in a word from a stream until limit is reached.
 * 
 * @param s the char pointer to array s
 * @param limit the length of array s
 * @param stream the source of the words
 * @return EOF if we have reached the end
 */
int getword(char *s, int limit, FILE *stream) {
	int c;
	char *w = s;
	assert(limit > 0 && s != NULL && stream != NULL);

	/* Skip to the start of the word */
	while (!isalnum(c = getc(stream)) && EOF != c)
		;
	if (EOF == c) {
		return EOF;
	} else if (--limit > 0) { /* Reduce limit by 1 to allow for the \0 */
		*w++ = tolower(c);
	}
	while (--limit > 0) {
		if (isalnum(c = getc(stream))) {
			*w++ = tolower(c);
		} else if ('\'' == c) {
			limit++;
		} else {
			break;
		}
	}
	*w = '\0';
	return w - s;
}

/**
 * Checks if a number is a prime number.
 *
 * @param  n The number to check
 * @return 0 For False and 1 for True
 */
int is_prime(int n) {
	int i, root;

	/* Boundary cases */
	if (n % 2 == 0 || n % 3 == 0) return 0;

	root = (int) sqrt(n);

	/* All primes greater than 6 are of the form 6k + 1 */
	for (i = 5; i <= root; i += 6) if (n % i == 0) return 0;
	for (i = 7; i <= root; i += 6) if (n % i == 0) return 0;

	return 1;
}
