#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PERIMETER_DOUBLE 2

// Function to calculate the squared distance between two points
double DistanceSquared(double x1, double y1, double x2, double y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}
// Function to calculate the actual distance between two points
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Function to determine if four points form a rectangle
bool IsRectangle(double points[4][2]) {
    // Compute all pairwise distances
    double distances[6];
    int k = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            distances[k++] = DistanceSquared(points[i][0], points[i][1], points[j][0], points[j][1]);
        }
    }

    // Sort the distances 
    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (distances[j] > distances[j + 1]) {
                double temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
            }
        }
    }

    // Validate rectangle properties:
    // - The smallest four distances are the sides (two pairs of equal sides).
    // - The largest two distances are the diagonals (equal).
    return fabs(distances[0] - distances[1]) < 1e-6 &&   // First pair of sides equal
        fabs(distances[2] - distances[3]) < 1e-6 &&   // Second pair of sides equal
        fabs(distances[4] - distances[5]) < 1e-6;     // Diagonals equal
}

// Main function
void RectangleSolver() {
    double points[4][2];
    double perimeter = 0;
    double distances[6];

    //Sides
    double side1 = 0;
    double side2 = 0;

    //Enter coordinates
    printf("Enter the coordinates of four points (x, y) in any order:\n");
    for (int i = 0; i < 4; i++) {
        printf("Point %d (format x y): ", i + 1);
        if (scanf("%lf %lf", &points[i][0], &points[i][1]) != 2) {
            printf("Invalid input. Please enter numbers.\n");
            i--; // Retry the current point
        }
    }

    if (IsRectangle(points)) {
        // Compute pairwise distances
        int k = 0;

        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                distances[k++] = distance(points[i][0], points[i][1], points[j][0], points[j][1]);
            }
        }

        // Sort the distances
        for (int i = 0; i < 6 - 1; i++) {
            for (int j = 0; j < 6 - i - 1; j++) {
                if (distances[j] > distances[j + 1]) {
                    double temp = distances[j];
                    distances[j] = distances[j + 1];
                    distances[j + 1] = temp;
                }
            }
        }

        // The two smallest distances are the sides of the rectangle
        side1 = distances[0];
        side2 = distances[2];

        // Calculate perimeter and area
        perimeter = PERIMETER_DOUBLE * (side1 + side2);
        double area = side1 * side2;

        printf("The points form a rectangle.\n");
        printf("Perimeter: %.2f\n", perimeter);
        printf("Area: %.2f\n", area);
    }
    else {

        side1 = distances[0];
        side2 = distances[2];

        //Just perimeter
        perimeter = PERIMETER_DOUBLE * (side1 + side2);

        printf("The points selected do not form a rectangle.\n");
        printf("Perimeter: %.2f\n", perimeter);


    }
}

