// File:   lowpassfil.c
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

typedef struct {
    double x;
    double y;
    double z;
} Point;

double dotProduct(Point v1, Point v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
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

int main() {
    Point A, B, C, P;
    // Get user input for the coordinates of A, B, C, and P
    printf("Enter the coordinates of point A (x y z): ");
    scanf("%lf %lf %lf", &A.x, &A.y, &A.z);
    // Repeat the above two lines for points B, C, and P
	printf("Enter the coordinates of point B (x y z): ");
    scanf("%lf %lf %lf", &B.x, &B.y, &B.z);
	// Repeat the above two lines for points B, C, and P
	printf("Enter the coordinates of point C (x y z): ");
    scanf("%lf %lf %lf", &C.x, &C.y, &C.z);
	// Repeat the above two lines for point P
	printf("Enter the coordinates of point P (x y z): ");
    scanf("%lf %lf %lf", &P.x, &P.y, &P.z);
    // Call the computeBarycentric function
    computeBarycentric(A, B, C, P);

    return 0;
}