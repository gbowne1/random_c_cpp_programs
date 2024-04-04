// File:   euclidianvectpr.c
// Author: Gregory K. Bowne
// Date:   12 OCT 2015
// Time:   9:01:22
// Brief:  A Euclidean vector space is a finite-dimensional inner product
// space over the real numbers. It is an affine space over the reals such
// that the associated vector space is a Euclidean space. In simpler terms,
// it is a space where vectors can be added together and multiplied by
// scalars, and it also has an associated inner product that allows the
// calculation of angles and lengths

#include <math.h>
#include <stdio.h>

typedef struct
{
	float x;
	float y;
	float z;
} Vector3D;

// Function to calculate the magnitude of a vector
float magnitude(Vector3D v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Function to calculate the dot product of two vectors
float dotProduct(Vector3D vector1, Vector3D vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

// Function to calculate the cross product of two vectors
Vector3D crossProduct(Vector3D vector1, Vector3D vector2)
{
	Vector3D result = {0.0f, 0.0f, 0.0f};
	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = vector1.z * vector2.x - vector1.x * vector2.z;
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	printf("Warning: Cannot calculate cross product of zero vectors");
	return result;
}

int main()
{
	// Example usage
	Vector3D vector1 = {1.0, 2.0, 3.0};
	Vector3D vector2 = {4.0, 5.0, 6.0};

	// Calculate the magnitude of vector a
	printf("Magnitude of a: %.2f\n", magnitude(vector1));

	// Calculate the dot product of vectors a and b
	printf("Dot product of a and b: %.2f\n", dotProduct(vector1, vector2));

	// Calculate the cross product of vectors a and b
	Vector3D cross = crossProduct(vector1, vector2);
	printf("Cross product of a and b: (%.2f, %.2f, %.2f)\n", cross.x, cross.y, cross.z);

	return 0;
}