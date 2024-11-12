#include <stdio.h>
#include <math.h>
#include "trianglechecker.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to get a valid side length from the user
double get_side_length(const char* prompt) 
{
    double length;
    while (1) 
    {
        printf("%s", prompt);
        if (scanf("%lf", &length) == 1 && length > 0) 
        {
            return length;
        }
        else 
        {
            printf("Invalid input. Please enter a positive number.\n");
            // Clear input buffer
            while (getchar() != '\n');
        }
    }
}

// Function to check if the three sides can form a triangle
int can_form_triangle(double a, double b, double c) 
{
    return (a + b > c) && (a + c > b) && (b + c > a);
}

// Function to calculate the angles of the triangle in degrees
void calculate_angles(double a, double b, double c, double* A, double* B, double* C) 
{
    *A = acos((b * b + c * c - a * a) / (2 * b * c)) * (180.0 / M_PI);
    *B = acos((a * a + c * c - b * b) / (2 * a * c)) * (180.0 / M_PI);
    *C = acos((a * a + b * b - c * c) / (2 * a * b)) * (180.0 / M_PI);
}

int main() 
{
    double a, b, c;
    double A, B, C;

    printf("Enter the side lengths of the triangle:\n");
    a = get_side_length("Side 1: ");
    b = get_side_length("Side 2: ");
    c = get_side_length("Side 3: ");

    if (can_form_triangle(a, b, c)) {
        printf("The side lengths can form a triangle.\n");
        calculate_angles(a, b, c, &A, &B, &C);
        printf("The angles of the triangle are:\n");
        printf("Angle A: %.2f°\n", A);
        printf("Angle B: %.2f°\n", B);
        printf("Angle C: %.2f°\n", C);
    }
    else 
    {
        printf("The side lengths cannot form a triangle.\n");
    }

    return 0;
}




































