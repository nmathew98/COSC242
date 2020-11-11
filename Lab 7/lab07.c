#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 100
#define STRING_LENGTH 80

void *emalloc(size_t s) {
	void *result = malloc(s);
	if (NULL == result){
		fprintf(stderr,"memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	return result;
}

void print_nums(char **a, int n, long unsigned int average) {
	if(n>0) {
		if(strlen(a[0]) >=average) {
			printf("%s\n", a[0]);
		}
    		print_nums(a+1, n-1, average);
	}
}

int main(void) {
	char *wordlist[ARRAY_SIZE];
	char word[STRING_LENGTH];
	int num_words = 0, i,total = 0;
	double average = 0.0;

	while(num_words < ARRAY_SIZE && 1 == scanf("%79s",word)) {
		wordlist[num_words] = emalloc(strlen(word) + 1 * sizeof wordlist[0]);
		strcpy(wordlist[num_words],word);
		num_words++;
	}

	for(i=0; i<num_words; i++) {
		total += strlen(wordlist[i]);
	}

	average = (double)total / (double)num_words;

	if (num_words > 0) {
		print_nums(wordlist, num_words, (long unsigned int)average+1);
		fprintf(stderr,"%.2f\n",average);
	}

	for (i = 0; i < num_words; i++) {
		free(wordlist[i]);
	}

	return EXIT_SUCCESS;
}
