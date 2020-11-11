/**
 * asgn.c
 *
 * Main application file.
 *
 * @author Naveen Mathew
 * @author Hugo Baird
 * @author Cedric Stephani
 */

#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mylib.h"
#include "htable.h"

/**
 * Prints the words and their frequency count to stdout.
 *
 * @param freq the number of times the words_stdin is repeated.
 * @param words_stdin the string itself which is counted.
 */
static void print_info(int freq, char *words_stdin) {
	printf("%-4d %s\n", freq, words_stdin);
}

/**
 * Prints usage information.
 */
void print_help() {
	fprintf(stderr,
	        "Usage: ./sample-asgn [OPTION]... <STDIN>\n\n");
	fprintf(stderr,
	        "Perform various operations using a hash table.  ");
	fprintf(stderr,
	        "By default, words are\n");
	fprintf(stderr,
	        "read from stdin and added to the hash table, before being printed out\n");
	fprintf(stderr,
	        "alongside their frequencies to stdout.\n\n");
	fprintf(stderr,
	        "-c FILENAME  Check spelling of words in FILENAME using words\n");
	fprintf(stderr,
	        "             from stdin as dictionary.  Print unknown words to\n");
	fprintf(stderr,
	        "             stdout, timing info & count to stderr (ignore -p)\n");
	fprintf(stderr,
	        "-d           Use double hashing (linear probing is the default)\n");
	fprintf(stderr,
	        "-e           Display entire contents of hash table on stderr\n");
	fprintf(stderr,
	        "-p           Print stats info instead of frequencies & words\n");
	fprintf(stderr,
	        "-s SNAPSHOTS Show SNAPSHOTS stats snapshots (if -p is used)\n");
	fprintf(stderr,
	        "-t TABLESIZE Use the first prime >= TABLESIZE as htable size\n\n");
	fprintf(stderr,
	        "-h           Display this message\n\n");
}

/**
 * See usage information above for information on what each option does.
 * If no option is chosen, input is read from stdin, added to a hash table and
 * printed out when program is terminated.
 *
 * @param argc the number of arguments passed
 * @param argv pointer to the list of arguments
 * @return EXIT_FAILURE when something goes wrong and EXIT_SUCCESS when
 * everything goes well
 */

int main(int argc, char **argv) {
	const char *optstring = "c:deps:t:h"; /* Format string to get options */
	int capacity = 113; /* Default capacity */
	hashing_t method = LINEAR_P; /* Linear probing by default */

	FILE *word_stream = NULL; /* Document file (if any) */
	htable h; /* Hash table */
	char word[256]; /* Store words from stdin */
	char option; /* Option flag */
	int prime_number;
	int counter = 0; /* Counters */

	/* Timing variables */
	double insert_time;
	clock_t start = 0, end = 0;

	/* To keep track of which options are used */
	int c = 0, e = 0, p = 0, num_stats = 10;

	/* Parse options */
	while ((option = getopt(argc, argv, optstring)) != EOF) {
		switch (option) {

		case 'c':
			/* Open up the document we want to check */
			if (NULL == (word_stream = fopen(optarg, "r"))) {
				fprintf(stderr, "Can't open file '%s' using mode r.\n", optarg);
				exit(EXIT_FAILURE);
			}
			c = 1;
			break;
		case 'd':
			method = DOUBLE_H;
			break;
		case 'e':
			e = 1;
			break;
		case 'p':
			p = 1;
			break;
		case 's':
			num_stats = atoi(optarg);
			break;
		case 't':
			prime_number = atoi(optarg) + 1;
			while (is_prime(prime_number) != 1) prime_number++;

			capacity = prime_number;
			break;
		case 'h':
			print_help();
			exit(EXIT_SUCCESS);
		default:
			print_help();
			exit(EXIT_FAILURE);
		}
	}

	/* Create a htable and start accepting input */
	h = htable_new(capacity, method);

	/* Insert words form stdin into htable, time it too */
	start = clock();
	while (getword(word, sizeof word, stdin) != EOF) {
		htable_insert(h, word);
	}
	end = clock();

	insert_time = (end - start) / (double) CLOCKS_PER_SEC;

	/* Display entire content of hash table on stderr */
	if (e) htable_print_entire_htable(h);
	if (e && !p && !c) htable_print(print_info, h);

	/* Print hash table stats. Only allow it if we aren't spell checking */
	if (p && !c) htable_print_stats(h, stdout, num_stats);

	/* Default option */
	if (!c && !e && !p) htable_print(print_info, h);

	/* If being used as spell checker */
	if (c) {
		counter = 0;

		/* Search the htable for our words, time it too */
		start = clock();
		while (getword(word, sizeof word, word_stream) != EOF) {
			if (htable_search(h, word) == 0) {
				counter++;
				printf("%s\n", word);
			}
		}
		end = clock();

		fclose(word_stream);

		/* Some stats for the nerds */
		fprintf(stderr, "Fill time     : %.6f\n", insert_time);
		fprintf(stderr, "Search time   : %.6f\n",
		        (end - start) / (double) CLOCKS_PER_SEC);
		fprintf(stderr, "Unknown words = %d\n", counter);
	}

	/* Apparently not freeing your memory is a bad thing D: */
	htable_free(h);

	return EXIT_SUCCESS;
}
