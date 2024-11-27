#include "RectangleSolver.h"
#include <math.h>
#include <stdbool.h>
#include <string.h> 

//Retireve input from the user for their shape - this is infinite for some reason
void InputPointsRectangle(double points[4][2]) {
    printf("Enter the coordinates of four points (x y):\n");

    for (int i = 0; i < 4; i++) {
        printf("Point %d (format x y): ", i + 1);

        //If 2 points werent inputed
        if (scanf("%lf %lf", &points[i][0], &points[i][1]) != 2) {

            printf("Invalid input. Please try again.\n");
            i--; // Return to the current point
        }
    }
    double sides[];
    getSides(points, sides[]);
}
double getSides(double points[4][2]) {
    double distances[6];
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            distances[k++] = DistanceSquared(points[i][0], points[i][1], points[j][0], points[j][1]);

        }
    }

    for (int i = 0; i < 7 - 1; i++) {
        for (int j = 0; j < 7 - i - 1; j++) {
            if (distances[j] > distances[j + 1]) {
                double temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;

            }

        }
    }
    double diagonal = distances[5];
    double diagonal1 = distances[6];

}

// Calculate the actual distance between two points
double Distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Calculate squared distance between two points
double DistanceSquared(double x1, double y1, double x2, double y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

// Function to determine if four points form a rectangle
bool IsRectangle(double points[4][2]) {

    //Check to see if all inputs are the same
    bool allPointsAreSame = true;


    //Iterate through points and compare them to see if they are the same
    for (int i = 0; i < 4; i++) {
        if (points[i][0] != points[0][0] || points[i][0] != points[0][1]) {
            allPointsAreSame = false;
            break; //exit loop
        }
    }

    //If all the points are the same return false, it is not a rectangle
    if (allPointsAreSame) {
        printf("Same points detected\n");
        return false;
    }


    // Find all six pairwise squared distances
    double distances[6];
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            distances[k++] = DistanceSquared(points[i][0], points[i][1], points[j][0], points[j][1]);
        }
    }

    // Sort the distances (smallest to largest)
    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (distances[j] > distances[j + 1]) {
                double temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
            }
        }
    }

    // Check rectangle properties:
    // - First two distances are equal (sides)
    // - Next two distances are equal (sides)
    // - Last two distances are equal (diagonals)
    return fabs(distances[0] - distances[1]) < 1e-6 &&  // First side pair equal
        fabs(distances[2] - distances[3]) < 1e-6 &&  // Second side pair equal
        fabs(distances[4] - distances[5]) < 1e-6 &&  // Diagonals equal
        fabs(distances[0] + distances[2] - distances[4]) < 1e-6;  // Pythagorean property
}


// Calculate the perimeter of four points
double CalculatePerimeter(double points[4][2]) {

    double perimeter = 0;

    printf("\n");

    for (int i = 0; i < 4; i++) {
        double dist = Distance(points[i][0], points[i][1], points[(i + 1) % 4][0], points[(i + 1) % 4][1]);
        printf("Distance between point %d and point %d: %.2f\n", i + 1, (i + 1) % 4 + 1, dist);  // Debugging line
        perimeter += dist;
       
    }

    printf("\n");

    return perimeter;
}

// Calculate the area of a rectangle 
double CalculateRectangleArea(double points[4][2]) {

    if (!IsRectangle(points)) {
        return -1; // Return -1 to indicate it's not a rectangle
    }

    double distances[6];
    int k = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            distances[k++] = DistanceSquared(points[i][0], points[i][1], points[j][0], points[j][1]);
        }
    }

    // Sort distances
    double sortedDistances[6];

    memcpy(sortedDistances, distances, 6 * sizeof(double));

    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (sortedDistances[j] > sortedDistances[j + 1]) {
                double temp = sortedDistances[j];
                sortedDistances[j] = sortedDistances[j + 1];
                sortedDistances[j + 1] = temp;
            }
        }
    }

    // Area = side1 * side2
    return sqrt(sortedDistances[0]) * sqrt(sortedDistances[2]);
}
