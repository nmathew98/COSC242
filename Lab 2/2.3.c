#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 10

int main(void) {
    int participants[ARRAY_SIZE];
    double judge1[ARRAY_SIZE], judge2[ARRAY_SIZE], judge3[ARRAY_SIZE];
    int curr_pos = 0;

    /* Load the data */
    while (4 == scanf("%d%lg%lg%lg", &participants[curr_pos], &judge1[curr_pos], &judge2[curr_pos], &judge3[curr_pos])) {
        printf("Read: %d %f %f %f\n", participants[curr_pos], judge1[curr_pos], judge2[curr_pos], judge3[curr_pos]);
        printf("Current position: %d\n", curr_pos);
        curr_pos++;
    }
    printf("\n");
    
    /* Calculate the means */
    double judge1_mean, judge2_mean, judge3_mean;
    judge1_mean = judge2_mean = judge3_mean = 0.0;
    int i;
    for (i = 0; i <= curr_pos; i++) {
        judge1_mean += judge1[i];
        if (i == curr_pos) {
            judge1_mean = judge1_mean / i;
        }
    }
    for (i = 0; i <= curr_pos; i++) {
        judge2_mean += judge2[i];
        if (i == curr_pos) {
            judge2_mean = judge2_mean / i;
        }
    }
    for (i = 0; i <= curr_pos; i++) {
        judge3_mean += judge3[i];
        if (i == curr_pos) {
            judge3_mean = judge3_mean / i;
        }
    }

    double judge1_sd, judge2_sd, judge3_sd;
    judge1_sd = judge2_sd = judge3_sd = 0.0;
    for (i = 0; i <= curr_pos; i++) {
        judge1_sd += pow(2, judge1[i] - judge1_mean);
        if (i == curr_pos) {
            printf("Variance: %f\n", judge1_sd / i);
            judge1_sd = sqrt(judge1_sd / i);
        }
    }
    for (i = 0; i <= curr_pos; i++) {
        judge2_sd += pow(judge2[i] - judge2_mean, 2);
        if (i == curr_pos) {
            judge2_sd = sqrt(judge2_sd / i);
        }
    }
    for (i = 0; i <= curr_pos; i++) {
        judge3_sd += pow(judge3[i] - judge3_mean, 2);
        if (i == curr_pos) {
            judge3_sd = sqrt(judge3_sd / i);
        }
    }

    printf("Judge 1 : %f %f\n", judge1_mean, judge1_sd);
    printf("Judge 2 : %f %f\n", judge2_mean, judge2_sd);
    printf("Judge 3 : %f %f\n", judge3_mean, judge3_sd);
    
    return EXIT_SUCCESS;
}
