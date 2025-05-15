#include <stdio.h>
#include <stdlib.h>

#define POUNDS_IN_KG 2.20462
#define STONES_IN_KG 0.157473
#define KG_IN_POUND 0.453592
#define KG_IN_STONE 6.35029

void convert_from_kg(float kg) {
    printf("\n%.2f kg is equivalent to:\n", kg);
    printf("  %.2f pounds\n", kg * POUNDS_IN_KG);
    printf("  %.2f stones\n", kg * STONES_IN_KG);
}

void convert_from_pounds(float lbs) {
    float kg = lbs * KG_IN_POUND;
    printf("\n%.2f pounds is equivalent to:\n", lbs);
    printf("  %.2f kg\n", kg);
    printf("  %.2f stones\n", kg * STONES_IN_KG);
}

void convert_from_stones(float stones) {
    float kg = stones * KG_IN_STONE;
    printf("\n%.2f stones is equivalent to:\n", stones);
    printf("  %.2f kg\n", kg);
    printf("  %.2f pounds\n", kg * POUNDS_IN_KG);
}

int main() {
    int choice;
    float weight;

    do {
        printf("\n=== Weight Converter ===\n");
        printf("1. Convert from kilograms (kg)\n");
        printf("2. Convert from pounds (lbs)\n");
        printf("3. Convert from stones\n");
        printf("4. Exit\n");
        printf("Choose an option (1-4): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter weight in kilograms: ");
                scanf("%f", &weight);
                convert_from_kg(weight);
                break;
            case 2:
                printf("Enter weight in pounds: ");
                scanf("%f", &weight);
                convert_from_pounds(weight);
                break;
            case 3:
                printf("Enter weight in stones: ");
                scanf("%f", &weight);
                convert_from_stones(weight);
                break;
            case 4:
                printf("Exiting the converter. Stay healthy!\n");
                break;
            default:
                printf("Invalid choice. Please select 1-4.\n");
        }

    } while (choice != 4);

    return 0;
}
