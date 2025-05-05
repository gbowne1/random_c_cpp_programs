// This program will compile under C89/C90 as it does not use C99 or later featuresw

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Define a structure for complex numbers
typedef struct
{
	double real;
	double imag;
} Complex;

// Function to add two complex numbers
Complex add(const Complex *a, const Complex *b)
{
	Complex result;
	result.real = a->real + b->real;
	result.imag = a->imag + b->imag;
	return result;
}

// Function to subtract two complex numbers
Complex subtract(const Complex *a, const Complex *b)
{
	Complex result;
	result.real = a->real - b->real;
	result.imag = a->imag - b->imag;
	return result;
}
// Function to multiply two complex numbers
Complex multiply(const Complex *a, const Complex *b)
{
	Complex result;
	result.real = a->real * b->real - a->imag * b->imag;
	result.imag = a->real * b->imag + a->imag * b->real;
	return result;
}

// Function to divide two complex numbers
Complex divide(const Complex *a, const Complex *b)
{
	double denominator = b->real * b->real + b->imag * b->imag;
	if (denominator == 0.0)
	{
		printf("Error: Division by zero.\n");
		return (Complex){0.0, 0.0}; // Return zero or handle the error as appropriate
	}
	Complex result;
	result.real = (a->real * b->real + a->imag * b->imag) / denominator;
	result.imag = (a->imag * b->real - a->real * b->imag) / denominator;
	return result;
}

// Function to calculate the magnitude of a complex number
double magnitude(const Complex *num)
{
	return sqrt(num->real * num->real + num->imag * num->imag);
}

// Function to calculate the conjugate of a complex number
Complex conjugate(const Complex *num)
{
	Complex conjugateNum;
	conjugateNum.real = num->real;
	conjugateNum.imag = -num->imag;
	return conjugateNum;
}

// Function to dynamically allocate memory for a vector of complex numbers
Complex *createComplexVector(int size)
{
	Complex *vector = (Complex *)malloc(size * sizeof(Complex));
	if (vector == NULL)
	{
		printf("Error: Memory allocation failed.\n");
		return NULL; // Return NULL if memory allocation fails
	}
	// Initialize elements to zero if memory allocation is successful
	for (int i = 0; i < size; i++)
	{
		vector[i].real = 0.0;
		vector[i].imag = 0.0;
	}
	return vector; // Return the allocated memory
}

// Function to free memory allocated for a vector of complex numbers
void freeComplexVector(Complex *vector)
{
	free(vector);
}

// Function to scale a vector by a scalar value
void scaleVector(Complex *vector, int size, double scalar)
{
	for (int i = 0; i < size; i++)
	{
		vector[i].real *= scalar;
		vector[i].imag *= scalar;
	}
}

// Function to calculate the dot product of two vectors of complex numbers
Complex dotProduct(Complex *vec1, Complex *vec2, int size)
{
	Complex result = {0.0, 0.0};

	for (int i = 0; i < size; i++)
	{
		result.real += vec1[i].real * vec2[i].real - vec1[i].imag * vec2[i].imag;
		result.imag += vec1[i].real * vec2[i].imag + vec1[i].imag * vec2[i].real;
	}

	return result;
}

// Function to calculate the cross product of two vectors of complex numbers
// Note: Cross product is not typically defined for complex numbers in the usual mathematical sense.
// This function calculates the product of the magnitudes and the sine of the angle difference.
Complex crossProduct(Complex *vec1, Complex *vec2)
{
	double real1 = vec1->real;
	double imag1 = vec1->imag;
	double real2 = vec2->real;
	double imag2 = vec2->imag;

	// Calculate the magnitude of the two complex numbers
	double magnitude1 = sqrt(real1 * real1 + imag1 * imag1);
	double magnitude2 = sqrt(real2 * real2 + imag2 * imag2);

	// Calculate the angle between the two complex numbers
	double angle = atan2(imag1, real1) - atan2(imag2, real2);

	// Calculate the cross product as the product of the magnitudes and the sine of the angle
	Complex result;
	result.real = magnitude1 * magnitude2 * sin(angle);
	result.imag = 0.0; // The imaginary part is always 0 for the cross product of two complex numbers

	return result;
}

int main()
{
	int size = 5; // Example size for the vector
	Complex *vector = createComplexVector(size);

	if (vector == NULL)
	{
		printf("Memory allocation failed.\n");
		return 1; // Exit with an error code
	}

	// Example usage
	Complex vec1[3] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
	Complex vec2[3] = {{2.0, 1.0}, {4.0, 3.0}, {6.0, 5.0}};
	Complex result[3];

	for (int i = 0; i < 3; i++)
	{
		result[i] = add(&vec1[i], &vec2[i]); // Add corresponding elements
		printf("Sum of vectors at index %d: %.2f + %.2fi\n", i, result[i].real, result[i].imag);
	}

	freeComplexVector(vector);

	return 0;
}