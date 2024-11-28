#include "RectangleSolver.h"
#include <math.h>
#include <stdbool.h>
#include <string.h> 

//Retireve input from the user for their shape
void InputPointsRectangle(double points[4][2]) {

    bool duplicatePoint = false;

        //Prompt
    printf("\n");
    printf("Enter coordinates of four points in any order: \n");

        //For each point request an input in (x y) format
    for (int i = 0; i < 4; i++) {

        while (true) {

            printf("Point %d (format x y): ", i + 1);

            //this is to specify the input format and figure out if the input 
            //is not in the format, this checks point i of (x and y)
            if (scanf("%lf %lf", &points[i][0], &points[i][1]) != 2) {

                //Error not in the right format
                printf("\n");
                printf("Invalid input. Please enter a coordinate.\n");
                while (getchar() != '\n');
                continue;
            }

            //Check to see if point entered is the same as another point 
            //entered before it

            for (int j = 0; j < i; j++) {

                if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    duplicatePoint = true;
                    break;
                }

            }

            //If there is a duplicate notify the user there was duplicate point(s)
            if (duplicatePoint) {

                printf("\n");
                printf("Same point detected. Please enter a different point.\n");

                continue;
            }

            break;

        }

    }
}

//New get sides function to calculate the right sides for a rectangle

void GetSides(double points[4][2], double sides[4]) {

    double distances[6] = { 0 };
    int k = 0;

    // Compute all pairwise distances
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            distances[k++] = Distance(points[i][0], points[i][1], points[j][0], points[j][1]);
        }
    }

    // Sort distances small to large to check rectangle
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            if (distances[j] > distances[j + 1]) {
                double temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
            }
        }
    }

    // Assign the first four (shortest) distances to sides
    for (int i = 0; i < 4; i++) {
        sides[i] = distances[i];
    }

        
    //Print sides
    printf("\n");
    printf("Sides:\n");
    for (int i = 0; i < 4; i++) {
        printf("%.2f ", sides[i]);
    }
    printf("\n");
}

// Calculate the actual distance between two points
double Distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Calculate squared distance between two points
double DistanceSquared(double x1, double y1, double x2, double y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

bool IsRectangle(double sides[4]) {

    double width1 = sides[0];
    double width2 = sides[1];
    double length1 = sides[2];
    double length2 = sides[3];


    //Extra validation incase there is any negative sides calculated
    for (int i = 0; i < 4; i++) {

        if (sides[i] < 0)
            return false;

    }

    if (width1 != length1 && width1 == width2 && length1 == length2) {

        //Is a rectangle
        return true;
    }
    else {

        //Not a rectangle
        return false;
    }

}

// Calculate the perimeter of four points
double CalculatePerimeter(double sides[4]) {

    
    double perimeter = 0;

    //add up all sides of the quad shape
    perimeter = sides[0] + sides[1] + sides[2] + sides[3];

    return perimeter;
   
}

// Calculate the area of a rectangle 
double CalculateRectangleArea(double sides[4]) {

    //Sorted array widths = [0][1] length = [2][3]
    double length = sides[2];
    double width = sides[0];

    double area = length * width;

    return area;
   
}
