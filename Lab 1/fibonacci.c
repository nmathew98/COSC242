#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	/* variable declarations */
	int f = 0;
	int g = 1;
	int count = 0;
	int temp = -1;

	for (count = 0; count < 40; count++) {
		printf("%d ", g);
		temp = g;
		g += f;
		f = temp;
		if (count > 0 && (count + 1) % 5 == 0) {
			printf("\n");
		}
	}

	return EXIT_SUCCESS;
}
