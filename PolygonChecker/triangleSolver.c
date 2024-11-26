#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "TriangleSolver.h"

//Pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Small epsilon value for floating-point comparison - Delete if needed 
#define EPSILON 1e-6

// Function to get a valid side length from the user
double GetSideLength(const char* prompt) 
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
bool CanFormTriangle(double sideA, double sideB, double sideC) 
{
    //check if positive numbers
    if (sideA > 0 && sideB > 0 && sideC > 0)
        return (sideA + sideB > sideC) && (sideA + sideC > sideB) && (sideB + sideC > sideA);
    else
        return false;
}

// Function to calculate the angles of the triangle in degrees
void CalculateAngles(double sideA, double sideB, double sideC, double* angleA, double* angleB, double* angleC) 
{
    *angleA = acos((sideB * sideB + sideC * sideC - sideA * sideA) / (2 * sideB * sideC)) * (180.0 / M_PI);
    *angleB = acos((sideA * sideA + sideC * sideC - sideB * sideB) / (2 * sideA * sideC)) * (180.0 / M_PI);
    *angleC = acos((sideA * sideA + sideB * sideB - sideC * sideC) / (2 * sideA * sideB)) * (180.0 / M_PI);
}

// Helper function for floating-point comparisons - Delete if uneeded
bool AreEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

char* FindTypeOfTriangle(double angleA, double angleB, double angleC) {


    double tolerance = 1e-6; // Allowable error for floating-point comparisons

    // Check if it is a valid triangle
    if (fabs(angleA + angleB + angleC - 180.0) < tolerance) {

        // Check for equilateral triangle
        if (fabs(angleA - angleB) < tolerance && fabs(angleB - angleC) < tolerance) {
            printf("The chosen angles create an Equilateral Triangle\n");
            return "Equilateral";
        }

        // Check for isosceles triangle (two angles are the same)
        if (fabs(angleA - angleB) < tolerance || fabs(angleB - angleC) < tolerance || fabs(angleA - angleC) < tolerance) {
            printf("The chosen angles create an Isosceles Triangle\n");

            // Check if it's also a right triangle
            if (fabs(angleA - 90.0) < tolerance || fabs(angleB - 90.0) < tolerance || fabs(angleC - 90.0) < tolerance) {
                printf("It is also a Right Triangle.\n");

                return "Right";
            }

            // Check for obtuse triangle (one angle > than 90)
            if (angleA > 90.0 || angleB > 90.0 || angleC > 90.0) {
                printf("It is also an Obtuse Triangle\n");

                return "IObtuse";
            }

            //Check for acute angle (all angles < 90)
            if(angleA < 90.0 && angleB < 90.0 && angleC < 90.0) {
                printf("It is also an Acute Triangle.\n");

                return "AIsosceles";
            }

            return "Isosceles";
        }


        // Check for scalene triangle (all angles are different)
        if (fabs(angleA - angleB) >= tolerance && fabs(angleB - angleC) >= tolerance && fabs(angleA - angleC) >= tolerance) {
            printf("The chosen angles create a Scalene Triangle\n");

            // Check if it's also acute (all angles less than 90)
            if (angleA < 90.0 && angleB < 90.0 && angleC < 90.0) {
                printf("It is also an Acute Triangle.\n");

                return "AScalene";
            }

            if (angleA > 90.0 || angleB > 90.0 || angleC > 90.0) {
                printf("It is also an Obtuse Triangle.\n");
                return "OScalene";
            } 

            return "Scalene";
        }
    }

    // If angles do not form a valid triangle
    printf("The chosen angles do not form a valid triangle.\n");
    return "NTriangle";
}