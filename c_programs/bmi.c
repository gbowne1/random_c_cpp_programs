/* Function to calculate and display BMI using US customary units (pounds, inches)
   BMI = (weight in pounds * 703) / (height in inches * height in inches)
   Prompts user for weight and height, then prints BMI result
*/

#include <stdio.h>

void calculate_bmi(void);

int main(void)
{
    calculate_bmi();
    return 0;
}

/* Prompts for input, computes BMI, and prints result */
void calculate_bmi(void)
{
    float weight; /* User's weight in pounds */
    float height; /* User's height in inches */
    float bmi;    /* Calculated BMI */

    printf("Enter weight in pounds: ");
    if (scanf("%f", &weight) != 1) {
        printf("Invalid input for weight.\n");
        return;
    }

    printf("Enter height in inches: ");
    if (scanf("%f", &height) != 1 || height <= 0) {
        printf("Invalid input for height.\n");
        return;
    }

    bmi = (weight * 703) / (height * height);
    printf("Your BMI is: %.2f\n", bmi);
}