#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "TriangleSolver.h"

//Pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

char* FindTypeOfTriangle(double angleA, double angleB, double angleC) {


    //1e-6 is the room for error (with floating point math)
    printf("\n");

    //Check to see if it is a triangle
    if (angleA + angleB + angleC == 180) {

        // Check for equilateral triangle (all angles are 60)
        if (fabs(angleA - 60.0) < 1e-6 && fabs(angleB - 60.0) < 1e-6 && fabs(angleC - 60.0) < 1e-6) {
            printf("The chosen sides creates an Equilateral Triangle\n");
            return "Equilateral";
        }

        // Check for isosceles triangle (two angles are the same)
        else if (fabs(angleA - angleB) < 1e-6 || fabs(angleB - angleC) < 1e-6 || fabs(angleA - angleC) < 1e-6) {
            printf("The chosen sides create an Isosceles Triangle\n");


            //Check if it is a right angle
            if (angleA == 90 || angleB == 90 || angleC == 90) {

                printf("It is a right angle.\n");
                return "Right";

            }
            else
            {
                return "Isosceles";
            }
                
        }

        // Check for obtuse triangle (one angle is greater than 90)
        else if (angleA > 90.0 || angleB > 90.0 || angleC > 90.0 && angleA + angleB + angleC == 180) {
            printf("The chosen sides create an Obtuse Triangle\n");
            return "Obtuse";
        }

    }
    
    // If none of the above, it must be an acute triangle (all angles less than 90)
    else {
        printf("The chosen sides create an Acute Triangle\n");
        return "NTriangle";
    }

    printf("\n");
}





































