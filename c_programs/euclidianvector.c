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

#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

// Function to calculate the magnitude of a vector
float magnitude(Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Function to calculate the dot product of two vectors
float dotProduct(Vector3D v1, Vector3D v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Function to calculate the cross product of two vectors
Vector3D crossProduct(Vector3D v1, Vector3D v2) {
    Vector3D result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

int main() {
    // Example usage
    Vector3D a = {1.0, 2.0, 3.0};
    Vector3D b = {4.0, 5.0, 6.0};

    // Calculate the magnitude of vector a
    printf("Magnitude of a: %.2f\n", magnitude(a));

    // Calculate the dot product of vectors a and b
    printf("Dot product of a and b: %.2f\n", dotProduct(a, b));

    // Calculate the cross product of vectors a and b
    Vector3D cross = crossProduct(a, b);
    printf("Cross product of a and b: (%.2f, %.2f, %.2f)\n", cross.x, cross.y, cross.z);

    return 0;
}