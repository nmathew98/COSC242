#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double s1, s2, s3;
    int return_code;
    
    printf("Please enter the first judge's scores:");
    fflush(stdout);
    return_code = scanf("%lg", &s1);
    if (return_code != 1) {
        printf("scanf returned code %d\n", return_code);
        return EXIT_FAILURE;
    }

    printf("Please enter the second judge's scores:");
    fflush(stdout);
    return_code = scanf("%lg", &s2);
    if (return_code != 1) {
        printf("scanf returned code %d\n", return_code);
        return EXIT_FAILURE;
    }

    printf("Please enter the third judge's scores:");
    fflush(stdout);
    return_code = scanf("%lg", &s3);
    if (return_code != 1) {
        printf("scanf returned code %d\n", return_code);
        return EXIT_FAILURE;
    }

    if (s1 < s2 && s1 < s3) {
        printf("%f\n", (s2+s3)/2);
    } else if (s2 < s1 && s2 < s3) {
        printf("%f\n", (s1+s2) / 2);
    } else {
        printf("%f\n (s1+s2) / 2);
    }

    return 0;
}
