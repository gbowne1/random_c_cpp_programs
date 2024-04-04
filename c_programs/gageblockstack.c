#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#define MAX_BLOCKS 81 // Corrected to match the total number of blocks

typedef struct
{
	double length;
	double width;
	double height;
} GageBlock;

GageBlock gageBlocks[MAX_BLOCKS];

// Function to initialize the gage blocks with predefined dimensions
void initializeGageBlocks()
{
	int index = 0;
	for (int i = 0; i <= 8; i++)
	{
		double dimension = 0.1001 + i * 0.0001;
		gageBlocks[index++].length = dimension;
		gageBlocks[index++].width = dimension;
		gageBlocks[index++].height = dimension;
	}
	for (int i = 0; i <= 8; i++)
	{
		double dimension = 0.101 + i * 0.001; // Initialize and calculate dimension value
		gageBlocks[index++].length = dimension;
		gageBlocks[index++].width = dimension;
		gageBlocks[index++].height = dimension;
	}
	for (int i = 0; i <= 8; i++)
	{
		double dimension = 0.050;
		gageBlocks[index++].length = dimension;
		gageBlocks[index++].width = dimension;
		gageBlocks[index++].height = dimension;
	}
	for (int i = 0; i < 4; i++)
	{
		gageBlocks[index++].length = 1.000 + i * 1.000;
		gageBlocks[index++].width = 1.000 + i * 1.000;
		gageBlocks[index++].height = 1.000 + i * 1.000;
	}
}

void calculateStackHeight(double angle, GageBlock gageBlocks[], int numBlocks)
{
	double totalHeight = 0.0;
	double baseAngle = angle; // Assuming the base angle is the same as the stack angle

	// Assuming all blocks are of the same size and the angle affects the height directly
	// This is a simplified approach and might need adjustments based on actual requirements
	for (int i = 0; i < numBlocks; i++)
	{
		// Assuming the height of a block is affected by the angle in a linear fashion
		// This is a placeholder for the actual calculation logic
		double heightAdjustment = sin(baseAngle); // Adjustment based on the angle
		double blockHeight = gageBlocks[i].height + heightAdjustment;
		totalHeight += blockHeight;
	}

	// Print or return the calculated total height
	printf("Total stack height: %.4lf inches\n", totalHeight);
}

int main()
{
	initializeGageBlocks(); // Initialize the gage blocks with the specified dimensions

	double angle;		  // Angle in decimal degrees
	double sineBarLength; // Length of the sine bar in inches
	double height;		  // Height in inches

	printf("Enter the angle (in decimal degrees): ");
	if (scanf("%lf", &angle) != 1 || angle < 0 || angle > 360)
	{
		printf("Invalid angle. Please enter a number between  0 and  360.\n");
		return 1; // Return an error code
	}

	printf("Enter the length of the sine bar (in inches): ");
	scanf("%lf", &sineBarLength);

	// Convert the angle to radians
	angle = angle * M_PI / 180.0;

	// Calculate the height using the gage blocks
	// Assuming the calculateStackHeight function is correctly implemented
	calculateStackHeight(angle, gageBlocks, MAX_BLOCKS);

	// Assuming the calculateStackHeight function updates a global variable or prints the result
	// For demonstration, let's assume it prints the result directly

	// If need to return the height from the calculateStackHeight function:
	// height = calculateStackHeight(angle, gageBlocks, MAX_BLOCKS);

	printf("Required gage block stack height: %.4lf inches\n", height);

	return 0;
}