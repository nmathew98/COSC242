#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 0;
    double a = 0, b = 0, c = 0;
    double scores = 0, highest_score = 0;
    int highest = 0;

    while(4 == scanf("%d%lg%lg%lg", &n, &a, &b, &c)) {
        if (a < b && a < c) {
            scores = (b + c) / 2;
        } else if (b < a && b < c) {
            scores = (a + c) / 2;
        } else {
            scores = (a + b) / 2;
        }

        if (scores > highest_score) {
            highest = n;
            highest_score = scores;
        }
    }
    printf("%d\n", highest);

    return EXIT_SUCCESS;
}

