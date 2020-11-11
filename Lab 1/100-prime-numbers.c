#include <stdio.h>
#include <stdlib.h>

int is_prime(int candidate) {
	int i = 2;
	for (i = 2; i < candidate; i++) {
		if (candidate % i == 0) {
			return 0;
		}
	}

	return 1;
}

int main(void) {
	int candidate = 2;
	int num_printed = 0;
	while (num_printed < 100) {
		if (is_prime(candidate)) {
			printf("%d ", candidate);
			num_printed++;
			if (num_printed % 5 == 0) {
				printf("\n");
			}
		}
		candidate++;
	}

	return 0;
}
