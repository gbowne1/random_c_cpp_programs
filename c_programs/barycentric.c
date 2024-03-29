// File:   barycentric.c
// Author: Gregory K. Bowne
// Date:   12 Sept 2023
// Time:   20:47:21
// Brief:  This program calculates the barycentric coordinates
//
// Barycentric coordinates are a coordinate system in which the location of a point is specified by reference to a simplex, such as a triangle or
// tetrahedron. They are used to represent points within the simplex and are particularly useful in triangle geometry for studying properties
// like Ceva's theorem, Routh's theorem, and Menelaus's theorem. In computer-aided design, they are useful for defining some kinds of Bézier
// surfaces.
//
// To compute barycentric coordinates for a point P with respect to a triangle (A, B, C), you can use the following method://
// Compute the barycentric coordinates (u, v, w) for point P using the following formula:
// This method computes the barycentric coordinates directly from the dot products of the vectors and the point, without the need for
// intermediate calculations.

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
    double z;
} Point;

typedef struct {
    Point v0;
    Point v1;
    double d00;
    double d01;
    double d11;
    double invDenom;
} TriangleCache;

double dotProduct(Point v1, Point v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

TriangleCache cacheTriangle(Point A, Point B, Point C) {
    TriangleCache cache;
    cache.v0 = (Point){B.x - A.x, B.y - A.y, B.z - A.z};
    cache.v1 = (Point){C.x - A.x, C.y - A.y, C.z - A.z};
    cache.d00 = dotProduct(cache.v0, cache.v0);
    cache.d01 = dotProduct(cache.v0, cache.v1);
    cache.d11 = dotProduct(cache.v1, cache.v1);
    double denom = cache.d00 * cache.d11 - cache.d01 * cache.d01;
    // Check for division by zero
    if (denom == 0) {
        printf("Error: Division by zero. The triangle is degenerate.\n");
        exit(EXIT_FAILURE);
    }
    cache.invDenom = 1.0 / denom;
    return cache;
}

Point getPointInput(const char* prompt) {
    Point p;
    printf("%s", prompt);
    if (scanf("%lf %lf %lf", &p.x, &p.y, &p.z) != 3) {
        printf("Invalid input. Please enter valid coordinates.\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

void computeBarycentric(Point A, Point B, Point C, Point P) {
    Point v0 = {B.x - A.x, B.y - A.y, B.z - A.z};
    Point v1 = {C.x - A.x, C.y - A.y, C.z - A.z};
    Point v2 = {P.x - A.x, P.y - A.y, P.z - A.z};

    double d00 = dotProduct(v0, v0);
    double d01 = dotProduct(v0, v1);
    double d11 = dotProduct(v1, v1);
    double d20 = dotProduct(v2, v0);
    double d21 = dotProduct(v2, v1);

    double denom = d00 * d11 - d01 * d01;
    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1 - v - w;

    printf("Barycentric coordinates (u, v, w) for point P: (%f, %f, %f)\n", u, v, w);
}

int isValidInput(double value) {
    // Example: Check if value is a number and within a reasonable range
    return value >= -1e6 && value <= 1e6;
}

double crossProductMagnitude(Point v1, Point v2) {
    double x = v1.y * v2.z - v1.z * v2.y;
    double y = v1.z * v2.x - v1.x * v2.z;
    double z = v1.x * v2.y - v1.y * v2.x;
    return sqrt(x * x + y * y + z * z);
}

bool isTriangleDegenerate(Point A, Point B, Point C) {
    Point v0 = {B.x - A.x, B.y - A.y, B.z - A.z};
    Point v1 = {C.x - A.x, C.y - A.y, C.z - A.z};
    double area = crossProductMagnitude(v0, v1);
    return area == 0;
}

int main() {

	Point A, B, C, P;

    // Get user input for the coordinates of A, B, and C
    A = getPointInput("Enter the coordinates of point A (x y z): ");
    B = getPointInput("Enter the coordinates of point B (x y z): ");
    C = getPointInput("Enter the coordinates of point C (x y z): ");

    if (isTriangleDegenerate(A, B, C)) {
        printf("The triangle is degenerate (area is zero). Please enter valid points.\n");
        return 1;
    }

    // Pre-calculate independent variables
    Point v0 = {B.x - A.x, B.y - A.y, B.z - A.z};
    Point v1 = {C.x - A.x, C.y - A.y, C.z - A.z};

    // Compute denom outside the loop for reuse
    double d00 = dotProduct(v0, v0);
    double d01 = dotProduct(v0, v1);
    double d11 = dotProduct(v1, v1);

	if (isTriangleDegenerate(A, B, C)) {
        printf("The triangle is degenerate (area is zero). Please enter valid points.\n");
        return 1;
    }

	// Call the computeBarycentric function with pre-calculated values
	Point v2 = {P.x - A.x, P.y - A.y, P.z - A.z};
	double d20 = dotProduct(v0, v2);
	double d21 = dotProduct(v1, v2);
	double denom = d00 * d11 - d01 * d01;
	double u = 1.0/denom*(d11*d20-d01*d21);
	double w = 1.0/denom*(d00*d21-d01*d20);
	double v = 1.0-u-w;
    // Call the computeBarycentric function
    computeBarycentric(A, B, C, P);

	printf("Barycentric coordinates (u, v, w) for point P: (%f, %f, %f)\n", u, v, w);

    return 0;
}