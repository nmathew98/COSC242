#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int cur_reg_number;
    double cur_judge_one, cur_judge_two, cur_judge_three;
    double cur_avg_score = 0.0;
    int highest_reg_number = 0;
    double highest_avg_score = 0.0;

    while (4 == scanf("%d%lg%lg%lg", &cur_reg_number, &cur_judge_one, &cur_judge_two, &cur_judge_three)) {
        cur_avg_score = (cur_judge_one + cur_judge_two + cur_judge_three) / 3;
        printf("Read: %d %f %f %f %f\n", cur_reg_number, cur_judge_one, cur_judge_two, cur_judge_three, cur_avg_score);
        if (cur_avg_score > highest_avg_score) {
            highest_avg_score = cur_avg_score;
            highest_reg_number = cur_reg_number;
        }
    }

    printf("The winning figure skater is (registration number): %d \n", highest_reg_number);

    return EXIT_SUCCESS;
}
